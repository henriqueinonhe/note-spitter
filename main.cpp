#include <QApplication>

#include <iostream>
#include <array>
#include <cmath>

#include "variations.h"

#include "intro.h"
#include "datahold.h"

#include <QDebug>

DataHold hold;

int main(int argc, char *argv[])
{

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

    /*
    QApplication a(argc, argv);
    Intro introWindow;
    introWindow.show();

    return a.exec();*/
}
