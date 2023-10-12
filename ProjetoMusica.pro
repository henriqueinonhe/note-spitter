
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
    symmetriccliches.cpp \
    symmetricclichesform.cpp \
    settingsform.cpp \
    variationsform.cpp

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
    symmetriccliches.h \
    symmetricclichesform.h \
    settingsform.h \
    variationsform.h

FORMS += \
    intro.ui \
    rhythmicsetupform.ui \
    outputdialog.ui \
    melodicsetupform.ui \
    symmetricclichesform.ui \
    settingsform.ui \
    variationsform.ui

RESOURCES += \
    midiheader.qrc
