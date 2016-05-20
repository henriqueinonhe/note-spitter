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

    QApplication a(argc, argv);
    Intro introWindow;
    introWindow.show();

    return a.exec();
}
