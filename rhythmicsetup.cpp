#include "rhythmicsetup.h"

//Public

bool RhythmicSetup::setSlurChance(int _value)
{
    if(_value <= 100)
    {
        slurChance = _value;
        return true;
    }
    else return false;
}

void RhythmicSetup::setCellsWeight(std::array<int, cellsTotal> _array)
{
    for(int _index = 0; _index < cellsTotal; _index++)
    {
        cellsWeight[_index] = _array[_index];
    }
}



//Private

void RhythmicSetup::formatWeightRhythmic()
{
    //Formatting cellsWeight to further use

    int _cellNumber = 0, _index2 = 0;
    for(_cellNumber = 0; _cellNumber < cellsTotal; _cellNumber++)
    {
        for(_index2 = 0; _index2 < cellsWeight[_cellNumber]; _index2++)
        {
            formattedCellsWeight.push_back(_cellNumber);
        }
    }
}

