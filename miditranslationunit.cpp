#include "miditranslationunit.h"

MidiTranslationUnit::MidiTranslationUnit()
{

}

bool MidiTranslationUnit::setInputFileAddress(const std::string &_address)
{
    inputFile.open(_address, std::ios::in | std::ios::binary);

    return inputFile.is_open();
}

bool MidiTranslationUnit::setOutputFileAddress(const std::string &_address)
{
    outputFile.open(_address, std::ios::out | std::ios::binary);

    return outputFile.is_open();
}

bool MidiTranslationUnit::setSampleHeaderAddress(const std::string &_address)
{
    sampleHeader.open(_address, std::ios::in | std::ios::binary);

    return sampleHeader.is_open();
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

}

void MidiTranslationUnit::readToInput()
{
    /* This routine writes the data from the inputFile to inputData for
     * further processing. */

    int _fileLength;

    /* Gets the length of the file, then sets the iterator to the beggining
     * of the file. */
    inputFile.seekg(0, std::ios_base::end);
    _fileLength = inputFile.tellg();
    inputFile.seekg(0, std::ios_base::beg);

    /* Allocates enough space in the vector. */
    inputData.reserve(_fileLength);

    /* Read the data to the vector. */
    inputFile.read((char *) inputData.data(), _fileLength);
}

void MidiTranslationUnit::setAttributesFromInput()
{
    /* Sets the attributes from Midi Translation Unit
     * from the inputFile. */

    const static unsigned int headerEndPos = 0x68;
    const static unsigned int byteNumberPos = 0x43;



}

void MidiTranslationUnit::readTimeClock()
{
    /* Reads the time clock and unformats it. */
    const static unsigned int timeClockPos = 0x0c;

    timeClock = NumCon::convertFromVector(inputData, 16, 0x0c, 0x0c + 1);

}

void MidiTranslationUnit::readTimeSigature()
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
    unsigned long _max;

    if(_byteNumber == 0) return 0;
    else
    {
        _max = 0x7f;
        for(int j = 1; j < _byteNumber; j++)
        {
            _max += 0x7f*std::pow(2, (_byteNumber - 1)*(8 - 1));
        }
    }

    return _max;
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

    outputFile.seekp(headerEndPos, std::ios_base::beg);
    outputFile.write(reinterpret_cast<char*>(outputData.data()), outputData.size());

    //Writing Number of Bytes in the header
    //The format is always 4 bytes, so if there are less
    //than 4 bytes, we push the ones we have to the end
    //and insert the missing bytes at the beginning of the vector
    //with the value of 0x00
    std::vector<char> _buffer = NumCon::convertToVector(outputData.size() + trackHeaderByteComplement, 256, 4, ' ');
    outputFile.seekp(byteNumberPosition, std::ios_base::beg);
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
    outputFile.seekp(timeSignaturePosition, std::ios_base::beg);
    outputFile.write(reinterpret_cast<char*>(_buffer), 2);
}

void MidiTranslationUnit::writeTimeClock()
{
    //Writes the Time Clock
    static const unsigned int timeClockPosition = 0x0c;
    std::vector<char> _buffer = NumCon::convertToVector(timeClock, 256, 2, NUL);

    outputFile.seekp(timeClockPosition, std::ios_base::beg);
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






