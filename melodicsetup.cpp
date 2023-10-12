#include "melodicsetup.h"

void MelodicSetup::formatWeightMelodic()
{
    //Formatting notesWeight for further use
    NoteName _note;
    int _index = 0;

    for(_note = C; _note <= B; _note = static_cast<NoteName>(_note + 1))
    {
        for(_index = 0; _index < notesWeight[_note]; _index++)
        {
            formattedNotesWeight.push_back(_note);
        }
    }
    //Formatting intervalsWeight for further use
    IntervalName _interval;

    for(_interval = UNISON; _interval <= PERFECT_FIFTEENTH; _interval = static_cast<IntervalName>(_interval + 1))
    {
        for(_index = 0; _index < intervalsWeight[_interval]; _index++)
        {
            formattedIntervalsWeight.push_back(_interval);
        }
    }
}

void MelodicSetup::setNotesWeight(const std::array<int, notesTotal> &_array)
{
    for(int _index = 0; _index < notesTotal; _index++)
    {
        notesWeight[_index] = _array[_index];
    }
}

void MelodicSetup::setIntervalsWeight(const std::array<int, intervalsTotal> &_array)
{
    for(int _index = 0; _index < intervalsTotal; _index++)
    {
        intervalsWeight[_index] = _array[_index];
    }
}
