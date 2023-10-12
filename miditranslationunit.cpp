#include "miditranslationunit.h"

MidiTranslationUnit::MidiTranslationUnit()
{

}

bool MidiTranslationUnit::setInputFileAddress(const QString &_address)
{
    inputFile.setFileName(_address);
    inputFile.open(QFile::ReadOnly);

    return inputFile.isOpen();
}

bool MidiTranslationUnit::setOutputFileAddress(const QString &_address)
{
    outputFile.setFileName(_address);
    outputFile.open(QFile::WriteOnly);

    return outputFile.isOpen();
}

bool MidiTranslationUnit::setSampleHeaderAddress(const QString &_address)
{
    sampleHeader.setFileName(_address);
    sampleHeader.open(QFile::ReadOnly);

    return sampleHeader.isOpen();
}

void MidiTranslationUnit::setPulseMeasure(const PulseMeasureValidFigures _pulseMeasure)
{
    pulseMeasure = _pulseMeasure;
}

void MidiTranslationUnit::translateToMidi(const std::vector<Note> &_input)
{
    unsigned int _index = 0;
    //First Instruction
    outputData.push_back(0x00); //Delta time

    //The rest of the stream
    for(_index = 0; _index < _input.size(); _index++)
    {
        //If it is a pitched note
        if(!_input[_index].isRest())
        {
            outputData.push_back(0x90); //Note-On event
            outputData.push_back(_input[_index].getPitch()); //Pitch to turn on
            outputData.push_back(0x47); //Velocity
            //Delta time
            std::vector<unsigned char> _stream = formatTimeValue(_input[_index].getDuration());
            for(unsigned int _offset = 0; _offset < _stream.size(); _offset++)
            {
                outputData.push_back(_stream[_offset]);
            }

            outputData.push_back(0x80); //Note-Off event
            outputData.push_back(_input[_index].getPitch()); //Pitch to turn off
            outputData.push_back(0x00); //Release Time
            outputData.push_back(0x00); //Delta Time
        }
        //If it is a rest
        else
        {
            //Must erase previous note off delta time
            //because delta time after a note off is
            //interpreted as a rest
            outputData.pop_back(); //Erasing previous note off delta time

            std::vector<unsigned char> _stream = formatTimeValue(_input[_index].getDuration());
            for(unsigned int _offset = 0; _offset < _stream.size(); _offset++)
            {
                outputData.push_back(_stream[_offset]);
            }
        }
    }

    //If the last note is a rest it is not mentioned
    //because the last delta time is ommited
    if(_input.back().isRest())
    {
        //Pops out the last bytes that represent delta time
        unsigned int _byteNumber = formatTimeValue(_input.back().getDuration()).size();
        for(unsigned int _counter = 0; _counter < _byteNumber; _counter++)
        {
            outputData.pop_back();
        }
    }
    //If the last note is a pitched note we must erase the delta time (0x00)
    else outputData.pop_back();

    //Finishing bytes
    outputData.push_back(0x01);
    outputData.push_back(0xff);
    outputData.push_back(0x2f);
    outputData.push_back(0x00);
}

bool MidiTranslationUnit::translateToNote(std::vector<Note> &_output)
{
    /* This routine translates the content fetched from
     * the input File in the MIDI protocol to
     * the _output. */

    static const unsigned int headerEndPos = 0x68;
    static const Note _sampleNote;

    /* Treatment for the first note. */

    unsigned int _posIncrement;

    if(inputData[headerEndPos] == 0x00) //Which means first note is a pitched note and the next byte is 0x9x
    {
        _output.push_back(_sampleNote);

        _output.back().setPitch(inputData[headerEndPos + 2]);
        _output.back().setVelocity(inputData[headerEndPos + 3]);
        _output.back().setDuration(unformatTimeValuePitched(inputData, headerEndPos + 4));

        _posIncrement = 4 + byteNumberVlq(inputData, headerEndPos + 4);
    }
    else //Which means the first note is a rest note, so we only have to deal with the delta time
    {
        _output.push_back(_sampleNote);

        _output.back().setPitch(-1); //It is a rest, thus it is unpitched
        _output.back().setVelocity(0); //No velocity either
        _output.back().setDuration(unformatTimeValueRest(inputData, headerEndPos));

        _posIncrement = byteNumberVlq(inputData, headerEndPos);
    }

    /* Now we take care of the rest. */

    for(unsigned int _index = headerEndPos + _posIncrement; _index < inputData.size();)
    {
        if(inputData[_index] == 0x90) // I can generalize this later!
        {
            _output.push_back(_sampleNote);

            _output.back().setPitch(inputData[_index + 1]);
            _output.back().setVelocity(inputData[_index + 2]);
            _output.back().setDuration(unformatTimeValuePitched(inputData, _index + 3));

            _index += 3 + byteNumberVlq(inputData, _index + 3);
        }
        else if(inputData[_index] == 0x80) //Note off message, check for rest
        {
            /* inputData[_index + 1] = Pitch to be turned off.
             * inputData[_index + 2] = Release Time. */

            if(inputData[_index + 3] != 0x00 && inputData[_index + 3] != 0x01) //Which means it is a rest and not the last one
            {
                _output.push_back(_sampleNote);

                _output.back().setPitch(-1); //Unpitched;
                _output.back().setVelocity(0); //No velocity
                _output.back().setDuration(unformatTimeValueRest(inputData, _index + 3));

                _index += 3 + byteNumberVlq(inputData, _index + 3);
            }
            else
            {
                _index += 4;
            }
        }
        else //Any other messsage is just useless
        {
            _index++;
        }
    }
}

void MidiTranslationUnit::readToInput()
{
    /* This routine writes the data from the inputFile to inputData for
     * further processing. */

    int _fileLength;

    /* Gets the length of the file. */
    _fileLength = inputFile.size();

    /* Allocates enough space in the vector. */
    inputData.resize(_fileLength);

    /* Read the data to the vector. */
    inputFile.read((char *) inputData.data(), _fileLength);
}

double MidiTranslationUnit::unformatTimeValuePitched(const std::vector<unsigned char> &_vector, const int _beg)
{
    return static_cast<double>(vlqToInt(_vector, _beg)) / timeClock;
}

double MidiTranslationUnit::unformatTimeValueRest(const std::vector<unsigned char> &_vector, const int _beg)
{
    return -(static_cast<double>(vlqToInt(_vector, _beg)) / timeClock);
}

void MidiTranslationUnit::setAttributesFromInput()
{
    /* Sets the attributes from Midi Translation Unit
     * from the inputFile. */

    readToInput();
    readTimeClock();
    readTimeSignature();
}

void MidiTranslationUnit::readTimeClock()
{
    /* Reads the time clock and unformats it. */
    const static unsigned int timeClockPos = 0x0c;

    timeClock = NumCon::convertFromVector(inputData, 256 /* Size of a byte */, timeClockPos, 2);
}

void MidiTranslationUnit::readTimeSignature()
{
    /* Reads the time signature and "unformats" it. */
    const static unsigned int timeSignaturePos = 0x1a;

    pulseNumber = inputData[timeSignaturePos];
    switch(inputData[timeSignaturePos + 1])
    {
        case 1:
        pulseMeasure = MEASURE_HALF;
        break;

        case 2:
        pulseMeasure = MEASURE_QUARTER;
        break;

        case 3:
        pulseMeasure = MEASURE_EIGHTH;
        break;

        case 4:
        pulseMeasure = MEASURE_SIXTEENTH;
        break;

        case 5:
        pulseMeasure = MEASURE_THIRTYSECOND;
        break;
    }
}

std::vector<unsigned char> MidiTranslationUnit::dataToVlq(const unsigned long _value)
{
    //Converts the value to its correspondent VLQ representation
    //and stores it in a string
    std::vector<unsigned char> _stream;
    int _digit = byteNumberVlq(_value);

    for(int _offset = 0; _offset < _digit; _offset++)
    {
         _stream.push_back((_value % static_cast<unsigned long>(std::pow(0x80, _digit - _offset)))/
                           std::pow(0x80, _digit - _offset - 1) + 0x80);
    }
     _stream[_digit - 1] -= 0x80;

    return _stream;

}

unsigned long MidiTranslationUnit::maxValueVlq(const int _byteNumber)
{
    //Returns the maximum value represented byte
    //the _byteNumber byte VLQ representation

    if(_byteNumber == 0) return 0;
    else
    {
        std::vector<unsigned char> _vector(_byteNumber - 1, 0xff);
        _vector.push_back(0x7f);
        return vlqToInt(_vector, 0);
    }
}

int MidiTranslationUnit::byteNumberVlq(const unsigned long _value)
{
    /*Maybe this could be optimised using a value table
     * to do the conversions given the fact that
     * there aren't really many conversion options*/

    //Returns the number of bytes necessary to represent
    //the given _value in VLQ representation
    int _byteNumber = 0;

    //While the value (_value) being represented is greater
    //than the maximum value possible given by the actual _byteNumber
    //it increments the byte number;
    while(_value > maxValueVlq(_byteNumber)) _byteNumber++;

    return _byteNumber;
}

int MidiTranslationUnit::byteNumberVlq(const std::vector<unsigned char> &_vector, const int _beg)
{
    /* Returns the number of the given Vlq contained in the given vector
     * starting at pos _beg. */

    int _digitNum = 1;

    for(int _index = _beg; ;_index++)
    {
        if(_vector[_index] > 0x7f) _digitNum++;
        else break;
    }

    return _digitNum;
}

int MidiTranslationUnit::vlqToInt(const std::vector<unsigned char> &_vector, const int _beg)
{
    /* Converts a Variable Length Quantity stored in a vector,
     * to an integer, starting at position _beg of the vector. */

    /* First of all we need to know how many digits the vlq
     * is composed of. */

    int _digitNum = byteNumberVlq(_vector, _beg);
    unsigned int _int = 0;


    /* Then we convert the value. */
    for(int _i = 0; _i < _digitNum - 1; _i++)
    {
        _int += (_vector[_beg + _i] - 0x80) * std::pow(0x80, _digitNum - _i - 1);
    }
    _int += _vector[_beg + _digitNum - 1];

    return _int;
}

std::vector<unsigned char> MidiTranslationUnit::formatTimeValue(float _value)
{
    //Formats the value for input into dataOutput

    //Multiplication by the timeClock
    //Absolute Value because it doesn't matter whether it is a rest or note
    //And finally converts to VLQ representation

    return dataToVlq(std::abs(_value*timeClock));
}

void MidiTranslationUnit::writeToFile()
{
    writeToHeader();
    writeTimeClock();
    writeTimeSignature();
    writeData();
}

void MidiTranslationUnit::writeToHeader()
{
    //Writes the data from sampleHeader to the
    //target's header file

    static const unsigned int headerEndPos = 0x68;

    //Writes the header to the buffer
    char *_buffer = new char[headerEndPos];

    sampleHeader.read(_buffer, headerEndPos);
    outputFile.write(_buffer, headerEndPos);
}

void MidiTranslationUnit::writeData()
{
    //Writes the data from outputData to the outputFile, after the header
    static const unsigned int byteNumberPosition = 0x43;
    static const unsigned int trackHeaderByteComplement = 33;
    static const unsigned int headerEndPos = 0x68;

    outputFile.seek(headerEndPos);
    outputFile.write(reinterpret_cast<char*>(outputData.data()), outputData.size());

    //Writing Number of Bytes in the header
    //The format is always 4 bytes, so if there are less
    //than 4 bytes, we push the ones we have to the end
    //and insert the missing bytes at the beginning of the vector
    //with the value of 0x00
    std::vector<char> _buffer = NumCon::convertToVector(outputData.size() + trackHeaderByteComplement, 256, 4, ' ');
    outputFile.seek(byteNumberPosition);
    outputFile.write(reinterpret_cast<char*>(_buffer.data()), 4);

}

void MidiTranslationUnit::writeTimeSignature()
{
    //Writing the Time Signature
    static const unsigned int timeSignaturePosition = 0x1a;

    //Two bytes, the first one represents the pulseNumber
    //and the second one the pulseMeasure
    char *_buffer = new char[2];
    _buffer[0] = pulseNumber;
    _buffer[1] = (char) (pulseMeasure);
    outputFile.seek(timeSignaturePosition);
    outputFile.write(reinterpret_cast<char*>(_buffer), 2);
}

void MidiTranslationUnit::writeTimeClock()
{
    //Writes the Time Clock
    static const unsigned int timeClockPosition = 0x0c;
    std::vector<char> _buffer = NumCon::convertToVector(timeClock, 256, 2, NUL);

    outputFile.seek(timeClockPosition);
    outputFile.write(reinterpret_cast<char*>(_buffer.data()), 2);

}

void MidiTranslationUnit::setTimeClock(const int _clock)
{
    timeClock = _clock;
}

void MidiTranslationUnit::setPulseNumber(const int _pulseNumber)
{
    pulseNumber = _pulseNumber;
}






