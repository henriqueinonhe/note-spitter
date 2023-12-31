#ifndef MELODICSETUP_H
#define MELODICSETUP_H

#include <vector>
#include <array>
#include "musicenums.h"

class MelodicSetup
{
    public:
        static const int notesTotal = 12;
        static const int intervalsTotal = 25;

    protected:
        void formatWeightMelodic();
        void setNotesWeight(const std::array<int, notesTotal> &_array);
        void setIntervalsWeight(const std::array<int, intervalsTotal> &_array);
        int highestPitch;
        int lowestPitch;
        int firstPitch;
        std::array<int, notesTotal> notesWeight;
        std::array<int, intervalsTotal> intervalsWeight;
        std::vector<NoteName> formattedNotesWeight;
        std::vector<IntervalName> formattedIntervalsWeight;
        bool noLoop;
};

#endif
