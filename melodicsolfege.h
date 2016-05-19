#ifndef MELODICSOLFEGE_H
#define MELODICSOLFEGE_H

#include <time.h>

#include <vector>

#include "pcg_random.hpp"

#include "melodicsetup.h"
#include "rhythmicsetup.h"
#include "note.h"

class MelodicSolfege : public MelodicSetup, public RhythmicSetup
{
    public:
        MelodicSolfege(//Melodic Setup Attributes
                       const int _higestPitch,
                       const int _lowestPitch,
                       const int _firstPitch,
                       const std::array<int, notesTotal> &_notesWeightArray,
                       const std::array<int, intervalsTotal> &_intervalsWeightArray,
                       const bool _noLoop,
                       //Rhythmic Setup Attributes
                       const int _pulseNumber,
                       const PulseMeasureValidFigures _pulseMeasure,
                       const TimeSignatureMeter _meter,
                       const int _barNumber,
                       const int _slurChance,
                       const std::array<int, cellsTotal> &_cellsWeightArray);
        const std::vector<Note> &getNoteArray() const;
        pcg32 randomNumberGenerator;

    private:
        void setupRhythm();
        void setupMelody();
        void createCell(int _case);
        void newNote(double _duration);
        void newNote(double _duration, bool);
        void newRest(double _duration);
        bool hasSlur();
        double convertTimeMeasure(double _duration);
        unsigned char generatePitch();
        std::vector<Note> noteArray;
        bool firstNote;
};

#endif
