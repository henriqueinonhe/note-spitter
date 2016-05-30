#include <QApplication>

#include <iostream>
#include <array>
#include <cmath>

#include "variations.h"
#include "symmetriccliches.h"

#include "intro.h"
#include "datahold.h"

#include <QDebug>

DataHold hold;

int main(int argc, char *argv[])
{

    /*
    MidiTranslationUnit unit;

    unit.setInputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\Symmetric.mid");
    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\SymmetricOut.mid");
    unit.setSampleHeaderAddress("C:\\Users\\Henrique Inonhe\\Desktop\\NEWSAMPLE.mid");
    unit.readToInput();
    unit.setAttributesFromInput();

    Variations instance;

    std::vector<Note> stream;

    unit.translateToNote(stream);
    instance.setNoteInput(stream);

    instance.setHighestPitch(72);
    instance.setLowestPitch(60);
    instance.setStaticFirstNote(true);
    instance.generateNoteSequences();
    instance.formatToNoteOutput();

    unit.translateToMidi(instance.getNoteOutput());
    unit.writeToFile();
    */
    MidiTranslationUnit unit;

    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\ClichesOut.mid");
    unit.setSampleHeaderAddress("C:\\Users\\Henrique Inonhe\\Desktop\\NEWSAMPLE.mid");
    unit.setPulseNumber(4);
    unit.setPulseMeasure(MEASURE_QUARTER);
    unit.setTimeClock(960);

    std::vector<int> pattern = {2, 2, -1, -2, -2};

    SymmetricCliches instance(72, 48, 80, 1, 100, pattern);

    unit.translateToMidi(instance.getNoteOutput());
    unit.writeToFile();


    /*
    QApplication a(argc, argv);
    Intro introWindow;
    introWindow.show();

    return a.exec();*/
}
