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
#include "datahold.h"

#include <QDebug>

DataHold hold;

int main(int argc, char *argv[])
{
    /* Debugging section. */

    MidiTranslationUnit unit;

    std::vector<Note> test;

    unit.setInputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\MidiOutput.mid");
    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\MidiOutputCopy.mid");
    unit.setSampleHeaderAddress("C:\\Users\\Henrique Inonhe\\Desktop\\NEWSAMPLE.mid");
    unit.setAttributesFromInput();
    unit.translateToNote(test);
    unit.translateToMidi(test);
    unit.writeToFile();

    //QApplication a(argc, argv);
    //Intro introWindow;
    //introWindow.show();

    //return a.exec();
}
