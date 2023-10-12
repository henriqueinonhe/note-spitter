#ifndef VARIATIONS_H
#define VARIATIONS_H

#include <vector>
#include <cmath>
#include <array>

#include "note.h"
#include "musicenums.h"

class Variations
{
    public:
        Variations();
        void setHighestPitch(unsigned char _pitch);
        void setLowestPitch(unsigned char _pitch);
        void setNoteInput(const std::vector<Note> &_vector);
        void setStaticFirstNote(const bool _value);
        void setTimeSignature(const int _pulseNumber, const PulseMeasureValidFigures _pulseMeasure);
        void setAllowedIntervals(std::array<bool, 13> _array);
        std::vector<Note> &getNoteOutput();
        bool checkPitchRange();
        bool checkAdjRepeatedNotes();
        void generateNoteSequences();
        void formatToNoteOutput();

    private:
        void setMaximumDiff();
        void setIntervalBounds();
        void nextIntervalPattern(std::vector<int> &_pattern);
        bool checkAlternEnd(const std::vector<int> &_pattern);
        void nextAltern(std::vector<int> &_pattern);
        void resetAltern(std::vector<int> &_pattern);
        void nextComposition(std::vector<int> &_pattern);
        bool checkCompositionEnd(std::vector<int> &_pattern);
        void resetComposition(std::vector<int> &_pattern);
        void absIntervalBoundsFilter(std::vector<int> &_pattern);
        void fixLastElementOverflow(std::vector<int> &_pattern);
        bool lateFilter(const std::vector<int> &_pattern);
        bool checkIntervalAllowed(const int _interval);
        int highestPitch;
        int lowestPitch;
        int pulseNumber;
        PulseMeasureValidFigures pulseMeasure;
        int maximumDiff;
        int totalDiff;
        int noteNumber;
        int absAccumulatedIntervalBound;
        int leastAbsBound;
        bool staticFirstNote;
        std::vector<int> absIntervalBounds;
        std::vector<int> upperIntervalBounds;
        std::vector<int> lowerIntervalBounds;
        std::vector<int> pitchSequence;
        std::array<bool, 13> allowedIntervals;
        std::vector<std::vector<Note>> noteSequences;
        std::vector<Note> noteOutput;
        std::vector<Note> noteInput;
};

#endif // VARIATIONS_H
