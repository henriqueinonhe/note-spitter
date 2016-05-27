#include "symmetriccliches.h"

SymmetricCliches::SymmetricCliches()
{
    /* Debugging Purposes. */

}

void SymmetricCliches::setHighestPitch(unsigned char _pitch)
{
    highestPitch = _pitch;
}

void SymmetricCliches::setLowestPitch(unsigned char _pitch)
{
    lowestPitch = _pitch;
}

void SymmetricCliches::setNoteInput(const std::vector<Note> &_vector)
{
    noteInput = _vector;
}

bool SymmetricCliches::checkPitchRange()
{
    /* This routine checks if there is any note
     * in the noteInput which is out of bounds regarding
     * lowest and highest pitches. */

    for(unsigned int _index = 0; _index < noteInput.size(); _index++)
    {
        if(lowestPitch > noteInput[_index].getPitch() || highestPitch < noteInput[_index].getPitch())
        return false;
    }

    return true;
}

bool SymmetricCliches::checkAdjRepeatedNotes()
{
    /* Checks if there are any adjacent repeated notes.
     * Returns false if there are. */

    for(unsigned int _index = 1; _index < noteInput.size(); _index++)
    {
        if(noteInput[_index - 1].getPitch() == noteInput[_index].getPitch()) return false;
    }

    return true;
}

void SymmetricCliches::generateNoteSequences()
{
    /* This is the core function of this class,
     * it generates all of the note sequences,
     * which are the variations we are looking for. */

    /* The first sequence is obviously the inputNote sequence,
     * which is the base we are gonna work on. */

    setBaseSequence();

    std::vector<Note> _modelSequence; //This is basically the baseSequence but will be used as a model to generate other sequences
    totalDiff = 1; // Always starts at these values (x)
    partsNumber = 1;

    noteSequences.push_back(baseSequence); //noteSequences[0] = baseSequence;

    /* Then it generates the rest of the sequences
     * using intervalPatterns compositions. */

    while(totalDiff <= maximumDiff * noteNumber)
    {
        _modelSequence = baseSequence;
        nextIntervalPattern(intervalPattern);
        for(unsigned int _index; _index < intervalPattern.size(); _index++) //Applies the interval pattern to the base sequence
        {
            _modelSequence[_index].incrementPitch(intervalPattern[_index]);
        }
        noteSequences.push_back(_modelSequence); //Pushes back the altered sequence
    }
}

void SymmetricCliches::nextIntervalPattern(std::vector<int> &_pattern)
{
    /* This is the core function to generate the interval patterns
     * (enumerate them).
     * This proccess will be described thoroughly. */

    if(!checkAlternEnd(_pattern))
    {
        nextAltern(_pattern); // Process the next alternation
    }
    else if(partsNumber <= totalDiff)
    {
        resetAltern(_pattern); // Resets to the before first alternation
        nextComposition(_pattern); //Process the next composition
    }
    else
    {
        totalDiff++;
        partsNumber = 1;
    }
}

bool SymmetricCliches::checkAlternEnd(const std::vector<int> &_pattern) //Depois fazer uma versão generalizada de checks e modifiers em vetores
{
    /* Checks if all the alterning possibilities of the
     * interval pattern alterning have reached the end. */

    for(unsigned int _index = 0; _index < _pattern.size(); _index++)
    {
        if(_pattern[_index] > 0) return false;
    }

    return true;
}

void SymmetricCliches::nextAltern(std::vector<int> &_pattern)
{
    /* Generates the next alternation in the sequence. */

    int _index = 0;
    while(_pattern[_index] < 0)
    {
        _pattern[_index] *= -1;
        _index++;
    }
    _pattern[_index] *= -1;
}

void SymmetricCliches::resetAltern(std::vector<int> &_pattern)
{
    /* Resets to the before first alternation. */

    for(unsigned int _index = 0; _index < _pattern.size(); _index++)
    {
        _pattern[_index] *= -1;
    }
}

void SymmetricCliches::nextComposition(std::vector<int> &_pattern)
{
    /* Generates the next composiiton in the sequence. */

    if(!checkCompositionEnd(_pattern))
    {
        auto _iterator = _pattern.rbegin();

        if(*_iterator > 1)
        {
            while(*_iterator == 1) _iterator++;
            (*_iterator)--;
            (*(_iterator - 1))++;
        }
        else //*_iterator == 1
        {
            while(*(_iterator + 1) == 1) _iterator++;
            *(_iterator) = _pattern.back() + 1;
            (*(_iterator + 1))--;
            _pattern.back() = 1;
        }
    }
}

bool SymmetricCliches::checkCompositionEnd(std::vector<int> &_pattern)
{
    if(_pattern.back() > 1)
    {
        for(unsigned int _index = 0; _index < _pattern.size() - 1; _index)
        {
            if(_pattern[_index] != 1) return true;
        }
    }
    else return true;

    return false;
}

void SymmetricCliches::setBaseSequence()
{
    /* Sets the base sequence. */
    for(unsigned int _index = 0; _index < noteInput.size(); _index++)
    {
        baseSequence.push_back(noteInput[_index]);
    }

    //Sets noteNumber
    noteNumber = noteInput.size();
}



