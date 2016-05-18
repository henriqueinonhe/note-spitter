
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetoMusica
TEMPLATE = app

SOURCES += main.cpp \
    note.cpp \
    rhythmicsetup.cpp \
    melodicsetup.cpp \
    melodicsolfege.cpp \
    miditranslationunit.cpp \
    intro.cpp \
    melodicsetupform.cpp \
    rhythmicsetupform.cpp \
    outputdialog.cpp

HEADERS += \
    note.h \
    rhythmicsetup.h \
    melodicsetup.h \
    melodicsolfege.h \
    pcg_random.hpp \
    pcg_extras.hpp \
    miditranslationunit.h \
    musicenums.h \
    numericconverter.hpp \
    intro.h \
    melodicsetupform.h \
    rhythmicsetupform.h \
    outputdialog.h \
    datahold.h

FORMS += \
    intro.ui \
    melodicsetupform.ui \
    rhythmicsetupform.ui \
    outputdialog.ui

RESOURCES += \
    midiheader.qrc
