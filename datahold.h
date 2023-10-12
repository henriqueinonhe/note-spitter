#ifndef DATAHOLD_H
#define DATAHOLD_H

#include<array>
#include <string>

#include "melodicsetup.h"
#include "rhythmicsetup.h"

/* Not sure if this is the best way to do this,
 * but for this project it will do. */

class DataHold
{
    public:
    int highestPitch;
    int lowestPitch;
    int firstPitch;
    std::array<int, MelodicSetup::notesTotal> notesWeight;
    std::array<int, MelodicSetup::intervalsTotal> intervalsWeight;
    bool noLoop;
    int pulseNumber;
    PulseMeasureValidFigures pulseMeasure;
    TimeSignatureMeter meter;
    int barNumber;
    int slurChance;
    std::array<int, RhythmicSetup::cellsTotal> cellsWeight;
    std::string midiHeaderAddress;

};

#endif // DATAHOLD_H
