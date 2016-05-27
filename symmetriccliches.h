#ifndef SYMMETRICCLICHES_H
#define SYMMETRICCLICHES_H

#include <vector>

#include "note.h"

class SymmetricCliches
{
    public:
        SymmetricCliches();
        void setHighestPitch(unsigned char _pitch);
        void setLowestPitch(unsigned char _pitch);
        void setNoteInput(const std::vector<Note> &_vector);
        bool checkPitchRange();
        bool checkAdjRepeatedNotes();
        void generateNoteSequences();
        void formatToNoteOutput();

    private:
        void setBaseSequence();
        void setIntervalBounds();
        void nextIntervalPattern(std::vector<int> &_pattern);
        bool checkAlternEnd(const std::vector<int> &_pattern);
        void nextAltern(std::vector<int> &_pattern);
        void resetAltern(std::vector<int> &_pattern);
        void nextComposition(std::vector<int> &_pattern);
        bool checkCompositionEnd(std::vector<int> &_pattern);
        void maximumDiffFilter(std::vector<int> &_pattern);
        int highestPitch;
        int lowestPitch;
        int maximumDiff;
        int totalDiff;
        int partsNumber;
        int noteNumber;
        std::vector<int> intervalPattern;
        std::vector<int> intervalBounds;
        std::vector<std::vector<Note>> noteSequences;
        std::vector<Note> baseSequence;
        std::vector<Note> noteOutput;
        std::vector<Note> noteInput;
};

#endif // SYMMETRICCLICHES_H
