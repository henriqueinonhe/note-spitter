#include <QApplication>

#include <iostream>
#include <array>
#include <cmath>

#include "musicenums.h"
#include "miditranslationunit.h"
#include "melodicsolfege.h"
#include "pcg_random.hpp"
#include "numericconverter.hpp"

#include "intro.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Intro introWindow;
    introWindow.show();

    return a.exec();

    std::array<int, 12> notesWeight;
    std::array<int, 25> intervalsWeight;
    std::array<int, 9> cellsWeight;
    notesWeight.fill(0), intervalsWeight.fill(1), cellsWeight.fill(1);
    notesWeight[0] = 1;
    notesWeight[2] = 1;
    notesWeight[4] = 1;
    notesWeight[5] = 1;
    notesWeight[7] = 1;
    notesWeight[9] = 1;
    notesWeight[11] = 1;
    MelodicSolfege instance(79, //Highest Pitch
                            60, //Lowest Pitch
                            65, //First Pitch
                            notesWeight,
                            intervalsWeight,
                            true, //No Loop
                            7, //Pulse Number
                            MEASURE_QUARTER, //Pulse Measure
                            BINARY_METER, //Time Meter
                            50, //Bar Number
                            0, //Slur Chance
                            cellsWeight);
    MidiTranslationUnit unit;
    unit.setPulseNumber(7);
    unit.setPulseMeasure(MEASURE_QUARTER);
    unit.setTimeClock(960);
    unit.setSampleHeaderAddress("C:\\Users\\Henrique Inonhe\\Desktop\\Midi Study\\NEWSAMPLE.mid");
    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\MidiOutput.mid");
    unit.translateToMidi(instance.getNoteArray());
    unit.writeToFile();


    std::cout << "FINISHED!" << std::endl;

    /*This is a debug section to check if everything is allright*/

    float _duration = 0;
    for(unsigned int i = 0; i < instance.getNoteArray().size(); i++)
    {
        std::cout << "Duration: " << instance.getNoteArray()[i].getDuration()
                  << " " << "Pitch: "
                  << (int) instance.getNoteArray()[i].getPitch()
                  << std::endl;
        if(instance.getNoteArray()[i].getDuration() > 0)
            _duration += instance.getNoteArray()[i].getDuration();
        else _duration -= instance.getNoteArray()[i].getDuration();
    }

    std::cout << "Total Duration: " << _duration << std::endl;
}
