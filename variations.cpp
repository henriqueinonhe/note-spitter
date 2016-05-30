#include "variations.h"
#include <QDebug>
Variations::Variations()
{

}

void Variations::setHighestPitch(unsigned char _pitch)
{
    highestPitch = _pitch;
}

void Variations::setLowestPitch(unsigned char _pitch)
{
    lowestPitch = _pitch;
}

void Variations::setNoteInput(const std::vector<Note> &_vector)
{
    noteInput = _vector;
}

bool Variations::checkPitchRange()
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

bool Variations::checkAdjRepeatedNotes()
{
    /* Checks if there are any adjacent repeated notes.
     * Returns false if there are. */

    for(unsigned int _index = 1; _index < noteInput.size(); _index++)
    {
        if(noteInput[_index - 1].getPitch() == noteInput[_index].getPitch()) return false;
    }

    return true;
}

bool Variations::lateFilter(const std::vector<int> &_pattern)
{
    /* About boundaries. */

    for(unsigned int _index = 0; _index < _pattern.size(); _index++)
    {
        if(_pattern[_index] > 0 && _pattern[_index] > upperIntervalBounds[_index]) return false;
        else if(_pattern[_index] < 0 && std::abs(_pattern[_index]) > std::abs(lowerIntervalBounds[_index])) return false;
    }

    /* Then we test about interval direction preservation. */

    for(unsigned int _index = 0; _index < pitchSequence.size() - 1; _index++)
    {
        int baseInterval = pitchSequence[_index] - pitchSequence[_index + 1];
        if(baseInterval > 0 && baseInterval <= _pattern[_index] - _pattern[_index + 1]) return false;
        else if(baseInterval < 0 && baseInterval >= _pattern[_index + 1] - _pattern[_index]) return false;
    }

    /* I'll insert here another filter that will be treated separately. */

    for(unsigned int _index = 0; _index < _pattern.size() - 1; _index++)
    {
        if(!checkIntervalAllowed((pitchSequence[_index + 1] + _pattern[_index + 1]) -
                                 (pitchSequence[_index] + _pattern[_index]))) return false;
    }

    return true;
}

bool Variations::checkIntervalAllowed(const int _interval)
{
    return allowedIntervals[std::abs(_interval)];
}

void Variations::generateNoteSequences()
{
    /* This is the core function of this class,
     * it generates all of the note sequences,
     * which are the variations we are looking for. */

    setMaximumDiff(); //Sets the maximum Diff
    setIntervalBounds(); //Sets the intervalBounds

    std::vector<int> intervalPattern(noteNumber, 0); //Creates the intervalPattern note vector

    std::vector<Note> _baseSequence; //Base sequence which will be used to model other sequences
    totalDiff = 1; // Always starts at these values but later I can change this!
    intervalPattern.front() = totalDiff;

    noteSequences.push_back(noteInput); //noteSequences[0] = noteInput;

    /* Then it generates the rest of the sequences
     * using intervalPatterns compositions. */

    while(totalDiff <= absAccumulatedIntervalBound)
    {
        nextIntervalPattern(intervalPattern);
        if(lateFilter(intervalPattern))
        {
            _baseSequence = noteInput;
            for(unsigned int _index = 0; _index < intervalPattern.size(); _index++) //Applies the interval pattern to the base sequence
            {
                if(!_baseSequence[_index].isRest())
                _baseSequence[_index].incrementPitch(intervalPattern[_index]);
            }
            noteSequences.push_back(_baseSequence); //Pushes back the altered sequence
        }
    }
}

void Variations::nextIntervalPattern(std::vector<int> &_pattern)
{
    /* This is the core function to generate the interval patterns
     * (enumerate them). */

    if(!checkAlternEnd(_pattern))
    {
        nextAltern(_pattern); // Process the next alternation
    }
    else
    {
        resetAltern(_pattern); // Resets to the before first alternation
        nextComposition(_pattern); //Process the next composition
    }
}

bool Variations::checkAlternEnd(const std::vector<int> &_pattern) //Depois fazer uma versão generalizada de checks e modifiers em vetores
{
    /* Checks if all the alterning possibilities of the
     * interval pattern alterning have reached the end. */

    for(unsigned int _index = 0; _index < _pattern.size(); _index++)
    {
        if(_pattern[_index] > 0) return false;
    }

    return true;
}

void Variations::nextAltern(std::vector<int> &_pattern)
{
    /* Generates the next alternation in the sequence. */

    int _index = 0;
    while(_pattern[_index] <= 0)
    {
        _pattern[_index] *= -1;
        _index++;
    }
    _pattern[_index] *= -1;
}

void Variations::resetAltern(std::vector<int> &_pattern)
{
    /* Resets to the before first alternation. */

    for(unsigned int _index = 0; _index < _pattern.size(); _index++)
    {
        _pattern[_index] *= -1;
    }
}

void Variations::nextComposition(std::vector<int> &_pattern)
{
    /* Generates the next composiiton in the sequence. */

    if(!checkCompositionEnd(_pattern))
    {
        auto _iterator = _pattern.rbegin();

        if(*_iterator == 0)
        {
            while(*_iterator == 0) _iterator++;
            (*_iterator)--;
            (*(_iterator - 1))++;
        }
        else //*_iterator != 1
        {
            int _temp;
            while(*(_iterator + 1) == 0) _iterator++;
            _temp = _pattern.back(); //Swapping proccess
            _pattern.back() = *_iterator;
            *_iterator = _temp + 1;
            (*(_iterator + 1))--;
        }
    }
    else
    {
        totalDiff++;
        resetComposition(_pattern);
    }

    /* Then we apply the absIntervalBoundsFilter, if
     * totalDiff is greater than the lowest absIntervalBound.
     * (This is to optmize a little bit the proccess, though
     * its effectiveness may vary widely depending on the input). */

   // if(totalDiff > leastAbsBound) absIntervalBoundsFilter(_pattern);
}

void Variations::absIntervalBoundsFilter(std::vector<int> &_pattern)
{
    /* Here we will apply two filters which
     * toghether are very powerful to detain
     * unwanted compositions. */

    /* We fix the composition if needed
     * regarding the individual intervals' absolute
     * bounds. */

    /* If the "overflow" comes from the last element, we have
     * to deal with it in a special manner. */

    if(_pattern.back() > absIntervalBounds.back())
    {
        fixLastElementOverflow(_pattern);
        absIntervalBoundsFilter(_pattern);
    }
    else
    {
        for(unsigned int _index = 0; _index < _pattern.size() - 1; _index++)
        {
            if(_pattern[_index] > absIntervalBounds[_index])
            {
                int _temp;
                _temp = _pattern[_index];
                _pattern[_index] = absIntervalBounds[_index];
                _pattern[_index + 1] += _temp - _pattern[_index];
            }
        }
    }
}

void Variations::fixLastElementOverflow(std::vector<int> &_pattern)
{
    /* This function fixes the last element overflow. */

    auto _iterator = _pattern.rbegin();
    int _temp = (*_iterator - 1) + (*(_iterator + 1) - 1);
    _iterator++;
    while(_iterator + 1 != _pattern.rend() && *(_iterator + 1) == 1) _iterator++;
    if(_iterator + 1 != _pattern.rend())
    {
        (*(_iterator + 1))--;
        *_iterator = 1;
        *_iterator += _temp;
    }
}

void Variations::resetComposition(std::vector<int> &_pattern)
{
    /* Resets the pattern to the first state of the composition. */

    _pattern.front() = totalDiff;
    for(unsigned int _index = 1; _index < _pattern.size(); _index++)
    {
        _pattern[_index] = 0;
    }
}

bool Variations::checkCompositionEnd(std::vector<int> &_pattern)
{
    /* Checks if all the composition possibilites have been
     * exhausted within a certain totalDiff. */

    for(unsigned int _index = 0; _index < _pattern.size() - 1; _index++)
        {
            if(_pattern[_index] != 0) return false;
        }

        return true;
}

void Variations::setIntervalBounds()
{
    /* Sets the interval bounds of each note in the sequence. */

    absAccumulatedIntervalBound = 0;
    noteNumber = 0;
    int _lowerBound, _upperBound;

    for(int unsigned _index = 0; _index < noteInput.size(); _index++)
    {
        if(!noteInput[_index].isRest())
        {
            _upperBound = std::abs(noteInput[_index].getPitch() - highestPitch);
            _lowerBound = std::abs(noteInput[_index].getPitch() - lowestPitch);
            absIntervalBounds.push_back(_upperBound >= _lowerBound ? _upperBound : _lowerBound);
            upperIntervalBounds.push_back(_upperBound);
            lowerIntervalBounds.push_back(_lowerBound);
            absAccumulatedIntervalBound += absIntervalBounds[_index];
            noteNumber++;
        }
    }

    if(staticFirstNote) //The first note remains static throghout all the sequences
    {
        absAccumulatedIntervalBound -= absIntervalBounds.front();
        absIntervalBounds.front() = 0;
        upperIntervalBounds.front() = 0;
        lowerIntervalBounds.front() = 0;
    }

    /* Then it finds the leastAbsBound. */

    leastAbsBound = absIntervalBounds.front();
    for(unsigned int _index = 1; _index < absIntervalBounds.size(); _index++)
    {
        if(leastAbsBound > absIntervalBounds[_index])
        {
            leastAbsBound = absIntervalBounds[_index];
        }
    }

    /* Setting Pitches Sequence. */

    for(int _index = 0; _index < noteNumber; _index++)
    {
        if(!noteInput[_index].isRest()) pitchSequence.push_back(noteInput[_index].getPitch());
    }

    /* I have to fix this later. */
    allowedIntervals.fill(false);
    allowedIntervals[0] = true;
    allowedIntervals[1] = true;
    allowedIntervals[2] = true;
}

void Variations::setMaximumDiff()
{
    maximumDiff = highestPitch - lowestPitch;
}

void Variations::setStaticFirstNote(const bool _value)
{
    staticFirstNote = _value;
}

void Variations::formatToNoteOutput()
{
    /* This routine formats the noteSequence vector
     * to the noteOuput vector. */

    for(unsigned int _index = 0; _index < noteSequences.size(); _index++)
    {
        for(unsigned int _index2 = 0; _index2 < noteSequences[_index].size(); _index2++)
        {
            noteOutput.push_back(noteSequences[_index][_index2]);
        }
    }
}

std::vector<Note> &Variations::getNoteOutput()
{
    return noteOutput;
}

void Variations::setTimeSignature(const int _pulseNumber, const PulseMeasureValidFigures _pulseMeasure)
{
    pulseNumber = _pulseNumber;
    pulseMeasure = _pulseMeasure;
}
