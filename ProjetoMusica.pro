
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
    rhythmicsetupform.cpp \
    outputdialog.cpp \
    melodicsetupform.cpp \
    variations.cpp \
    variationsform.cpp \
    symmetriccliches.cpp

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
    rhythmicsetupform.h \
    outputdialog.h \
    datahold.h \
    melodicsetupform.h \
    pcg_uint128.hpp \
    variations.h \
    variationsform.h \
    symmetriccliches.h

FORMS += \
    intro.ui \
    rhythmicsetupform.ui \
    outputdialog.ui \
    melodicsetupform.ui \
    variationsform.ui

RESOURCES += \
    midiheader.qrc \
    midiheadersample.qrc

DISTFILES +=
