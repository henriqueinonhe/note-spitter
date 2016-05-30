#include "symmetriccliches.h"

SymmetricCliches::SymmetricCliches(const unsigned char _firstPitch,
                                   const double _firstDuration,
                                   const int _lowestPitch,
                                   const int _highestPitch,
                                   const int _cyclesNumber,
                                   const std::vector<int> &&_intervalPattern)
{
    firstPitch = _firstPitch;
    firstDuration = _firstDuration;
    lowestPitch = _lowestPitch;
    highestPitch = _highestPitch;
    ciclesNumber = _cyclesNumber;
    &intervalPattern = _intervalPattern;
}

void SymmetricCliches::setIntervalPattern(const std::vector<int> &_pattern)
{
    intervalPattern = _pattern;
}

std::vector<int> &SymmetricCliches::getNoteOutput() const
{
    return noteOutput;
}

void SymmetricCliches::generateNoteSequence()
{
    /* This is the core routine of this class,
     * which generates the note sequences when
     * the intervals are applied to the first note. */

    Note _sample(firstPitch, firstDuration);
    noteOutput.push_back(_sample);

    for(int _counter = 0; _counter < ciclesNumber; _counter++)
    {
        for(int _index = 0; _index < intervalPattern.size(); _index++)
        {
            _sample.incrementPitch(intervalPattern[_index]);
            if(!checkPitchBounds(_sample)) break;
            else noteOutput.push_back(_sample);
        }
        if(!checkPitchBounds(_sample)) break;
    }
}

bool SymmetricCliches::checkPitchBounds(const Note &_note)
{
    /* This routine checks if the note's pitch is
     * within bounds. */

    return lowestPitch <= _note.getPitch() && _note.getPitch() <= highestPitch;
}


