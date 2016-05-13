#include <iostream>
#include <array>
#include <cmath>

#include "musicenums.h"
#include "miditranslationunit.h"
#include "melodicsolfege.h"
#include "pcg_random.hpp"

int main()
{
    std::array<int, 12> notesWeight;
    std::array<int, 24> intervalsWeight;
    std::array<int, 9> cellsWeight;
    notesWeight.fill(1), intervalsWeight.fill(1), cellsWeight.fill(1);
    MelodicSolfege instance(79, //Highest Pitch
                            60, //Lowest Pitch
                            65, //First Pitch
                            notesWeight,
                            intervalsWeight,
                            true, //No Loop
                            4, //Pulse Number
                            MEASURE_HALF, //Pulse Measure
                            BINARY_METER, //Time Meter
                            20, //Bar Number
                            0, //Slur Chance
                            cellsWeight);
    MidiTranslationUnit unit;
    unit.setPulseNumber(4);
    unit.setPulseMeasure(MEASURE_HALF);
    unit.setTimeClock(960);
    unit.setSampleHeaderAddress("C:\\Users\\Henrique Inonhe\\Desktop\\Midi Study\\NEWSAMPLE.mid");
    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\MidiOutput.mid");
    unit.translateToMidi(instance.noteArray);
    unit.writeToFile();


    std::cout << "FINISHED!" << std::endl;

    /*This is a debug section to check if everything is allright*/

    float _duration = 0;
    for(unsigned int i = 0; i < instance.noteArray.size(); i++)
    {
        std::cout << "Duration: " << instance.noteArray[i].getDuration()
                  << " " << "Pitch: "
                  << (int) instance.noteArray[i].getPitch()
                  << std::endl;
        if(instance.noteArray[i].getDuration() > 0)
            _duration += instance.noteArray[i].getDuration();
        else _duration -= instance.noteArray[i].getDuration();
    }

    std::cout << "Total Duration: " << _duration << std::endl;
}
