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
                       int _higestPitch,
                       int _lowestPitch,
                       int _firstPitch,
                       std::array<int, notesTotal> _notesWeightArray,
                       std::array<int, intervalsTotal> _intervalsWeightArray,
                       bool _noLoop,
                       //Rhythmic Setup Attributes
                       int _pulseNumber,
                       PulseMeasureValidFigures _pulseMeasure,
                       TimeSignatureMeter _meter,
                       int _barNumber,
                       int _slurChance,
                       std::array<int, cellsTotal> _cellsWeightArray);
        std::vector<Note> getNoteArray();
        pcg32 randomNumberGenerator;

    private:
        void setupRhythm();
        void setupMelody();
        void createCell(int _case);
        void newNote(float _duration);
        void newRest(float _duration);
        bool hasSlur();
        float convertTimeMeasure(float _duration);
        unsigned char generatePitch();
        std::vector<Note> noteArray;
        bool firstNote;
};

#endif
