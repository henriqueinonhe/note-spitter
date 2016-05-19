#ifndef RHYTHMICSETUP_H
#define RHYTHMICSETUP_H

#include <vector>
#include <array>

#include "musicenums.h"

#ifndef NULL
#define NULL 0
#endif

class RhythmicSetup
{
    public:
        static const int cellsTotal = 63;

    protected:
        bool setSlurChance(const int _value);
        void setCellsWeight(const std::array<int, cellsTotal> &_array);
        void formatWeightRhythmic();
        int pulseNumber;
        PulseMeasureValidFigures pulseMeasure;
        TimeSignatureMeter meter;
        int barNumber;
        int slurChance;
        std::array<int, cellsTotal> cellsWeight;
        std::vector<int> formattedCellsWeight;
};

#endif
