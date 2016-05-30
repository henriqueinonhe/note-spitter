#ifndef SYMMETRICCLICHES_H
#define SYMMETRICCLICHES_H

#include "melodicsetup.h"
#include "note.h"

class SymmetricCliches : MelodicSetup
{
    public:
        SymmetricCliches(const unsigned char _firstPitch,
                         const double _firstDuration,
                         const int _lowestPitch,
                         const int _highestPitch,
                         const int _ciclesNumber,
                         const std::vector<int> &&_intervalPattern);
        void setIntervalPattern(const std::vector<int> &_pattern);
        std::vector<int> &getNoteOutput() const;
        void generateNoteSequence();

    private:
        bool checkPitchBounds(const Note &_note);
        std::vector<int> intervalPattern;
        std::vector<Note> noteOutput;
        int ciclesNumber;
        double firstDuration;

};

#endif // SYMMETRICCLICHES_H
