#include "melodicsolfege.h"

MelodicSolfege::MelodicSolfege(//Melodic Setup Attributes
                               const int _highestPitch,
                               const int _lowestPitch, int _firstPitch,
                               const std::array<int, notesTotal> &_notesWeightArray,
                               const std::array<int, intervalsTotal> &_intervalsWeightArray,
                               const bool _noLoop,
                               //Rhythmic Setup Attributes
                               const int _pulseNumber,
                               PulseMeasureValidFigures _pulseMeasure,
                               TimeSignatureMeter _meter,
                               const int _barNumber,
                               const int _slurChance,
                               const std::array<int, cellsTotal> &_cellsWeightArray) : firstNote(true)
{
    //Setting up the random number generator
    randomNumberGenerator.seed(time(NULL));

    //Setting up attributes and checking for any illegal values

    //MelodicSetup
    highestPitch = _highestPitch;
    lowestPitch = _lowestPitch;
    firstPitch = _firstPitch;
    this->setNotesWeight( _notesWeightArray);
    this->setIntervalsWeight(_intervalsWeightArray);
    this->formatWeightMelodic();
    noLoop = _noLoop;

    //RhythmicSetup
    pulseNumber = _pulseNumber;
    pulseMeasure = _pulseMeasure;
    meter = _meter;
    barNumber = _barNumber;
    this->setSlurChance(_slurChance); //Add fail setting signal
    this->setCellsWeight(_cellsWeightArray);
    this->formatWeightRhythmic();

    setupRhythm();

    setupMelody();
}

void MelodicSolfege::setupRhythm()
{
    //Setting Up Rhythm
    int _pulseTotal = pulseNumber*barNumber;
    for(int _pulse = 0; _pulse < _pulseTotal; _pulse++)
    {
        createCell(formattedCellsWeight[randomNumberGenerator(formattedCellsWeight.size())]);
    }
}

void MelodicSolfege::setupMelody()
{
    //Setting Up Pitches, rests doesn't have pitches

    //Setting Up First Pitch
    if(!noteArray[0].isRest()) noteArray[0].setPitch(firstPitch);


    //Following Pitches
    for(unsigned int _index = 1; _index < noteArray.size(); _index++)
    {
        if(!noteArray[_index].isRest()) noteArray[_index].setPitch(generatePitch());
    }
}

void MelodicSolfege::createCell(int _case)
{
    //Cells cases
    switch(_case)
    {
        //Q
        case 0:
        newNote(QUARTER);
        break;

        //q
        case 1:
        newRest(QUARTER);
        break;

        //E,E
        case 2:
        newNote(EIGHTH);
        newNote(EIGHTH);
        break;

        //E,e
        case 3:
        newNote(EIGHTH);
        newRest(EIGHTH);
        break;

        //e,E
        case 4:
        newRest(EIGHTH);
        newNote(EIGHTH);
        break;

        //S,S,S,S
        case 5:
        newNote(SIXTEENTH);
        newNote(SIXTEENTH);
        newNote(SIXTEENTH);
        newNote(SIXTEENTH);
        break;

        //E,S,S
        case 6:
        newNote(EIGHTH);
        newNote(SIXTEENTH);
        newNote(SIXTEENTH);
        break;

        //S,S,E
        case 7:
        newNote(SIXTEENTH);
        newNote(SIXTEENTH);
        newNote(EIGHTH);
        break;

        //S,E,S
        case 8:
        newNote(SIXTEENTH);
        newNote(EIGHTH);
        newNote(SIXTEENTH);
        break;

        //E+,S
        case 9:
        newNote(DOTTED_EIGHTH);
        newNote(SIXTEENTH);
        break;

        //S,E+
        case 10:
        newNote(SIXTEENTH);
        newNote(DOTTED_EIGHTH);
        break;

    }
}

void MelodicSolfege::newNote(double _duration)
{
    static Note _newNoteModel;

    //If it is note the first note
    //and if the slur isn't triggered or the previous note is a rest
    if(!firstNote && (!hasSlur() || noteArray.back().isRest()))
    {
        noteArray.push_back(_newNoteModel);
        noteArray.back().setDuration(convertTimeMeasure(_duration));
    }
    //If it is not the first note and therefore it has a slur
    //and Also previous note is not be a rest
    else if(!firstNote)
    {
        noteArray.back().incrementDuration(convertTimeMeasure(_duration));
    }
    //If it is the first note of the series
    else
    {
        noteArray.push_back(_newNoteModel);
        noteArray.back().setDuration(convertTimeMeasure(_duration));
        firstNote = false;
    }
}

void MelodicSolfege::newRest(double _duration)
{
    static Note _newRestModel;

    //If the previous note is a rest and note the first note
    if(!firstNote && noteArray.back().isRest())
    {
        noteArray.back().incrementDuration(convertTimeMeasure(-_duration)); //Duration is negative when it is a rest
    }
    //If it is note the first note and the previous one isn't
    //a rest (it means it is a pitched note)
    else if(!firstNote && !noteArray.back().isRest())
    {
        noteArray.push_back(_newRestModel);
        noteArray.back().setDuration(convertTimeMeasure(-_duration)); //Duration is negative when it is a rest
    }
    //If it is the first note of the series
    else
    {
        noteArray.push_back(_newRestModel);
        noteArray.back().setDuration(convertTimeMeasure(-_duration));
        firstNote = false;
    }
}

bool MelodicSolfege::hasSlur()
{
    return randomNumberGenerator(100) < static_cast<unsigned int>(slurChance);
}

double MelodicSolfege::convertTimeMeasure(double _duration)
{
    switch(pulseMeasure)
    {
        case MEASURE_HALF: return _duration/6;
        case MEASURE_QUARTER: return _duration/12;
        case MEASURE_EIGHTH: return _duration/24;
        case MEASURE_SIXTEENTH: return _duration/48;
        case MEASURE_THIRTYSECOND: return _duration/96;
    }
}

unsigned char MelodicSolfege::generatePitch() /*This can be optimized*/
{
    //Generating random pitch inside matching the conditions

    unsigned char _intervalsWeightRange = formattedIntervalsWeight.size();
    unsigned char _notesWeightRange = formattedNotesWeight.size();
    static unsigned char _previousNote = firstPitch;
    static unsigned char _beforePreviousNote = 0;
    int _actualInterval;
    unsigned char _actualNote;
    unsigned char _noteCheck;
    int _sign;


    //Now it tries to find a random number inside boudaries that satisfies
    //the conditions
    do
    {
        //First it generates an (absolute) interval according to the set
        //probabilities
        _actualInterval = formattedIntervalsWeight[randomNumberGenerator(_intervalsWeightRange)];

        //Then it generates the sign of the interval (ascending or descending)
        switch(randomNumberGenerator(2))
        {
            case 0:
            _sign = -1;
            break;
            case 1:
            _sign = 1;
            break;
        }

        //Now we generate the actual note which is equal to
        //the previous note plus the actual interval ascending or descending
        _actualNote = _previousNote + _actualInterval*_sign;

        //Note probability check call
        _noteCheck = formattedNotesWeight[randomNumberGenerator(_notesWeightRange)];

        //For the pitch to be set it needs to satisfy the following conditions:
        //1 - Be withing pitch bounds
        //2 - Satisfy the "probability check call"
        //3 - If noLoop is true the note before the previous cannot be
        //equal the next
        //Which means it's gonna loop WHILE it doesn't satisfy the above conditions
    }while(!(lowestPitch <= _actualNote &&
             _actualNote <= highestPitch &&
             _actualNote%12 == _noteCheck &&
             (noLoop || _actualNote != _beforePreviousNote)));

    //Setting things up for the next call
    _beforePreviousNote = _previousNote;
    _previousNote = _actualNote;

    return _actualNote;
}

const std::vector<Note> &MelodicSolfege::getNoteArray() const
{
    return noteArray;
}









