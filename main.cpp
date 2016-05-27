#include <QApplication>

#include <iostream>
#include <array>
#include <cmath>

#include "symmetriccliches.h"

#include "intro.h"
#include "datahold.h"

#include <QDebug>

DataHold hold;

int main(int argc, char *argv[])
{
    MidiTranslationUnit unit;

    unit.setInputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\Symmetric.mid");
    unit.readToInput();

    SymmetricCliches instance;

    std::vector<Note> stream;

    unit.translateToNote(stream);
    instance.setNoteInput(stream);

    instance.generateNoteSequences();

    QApplication a(argc, argv);
    Intro introWindow;
    introWindow.show();

    return a.exec();
}
