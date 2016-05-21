
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
    Forms Sources/intro.cpp \
    Forms Sources/melodicsetupform.cpp \
    Forms Sources/outputdialog.cpp \
    Forms Sources/rhythmicsetupform.cpp \
    Forms Sources/intro.cpp \
    Forms Sources/melodicsetupform.cpp \
    Forms Sources/outputdialog.cpp \
    Forms Sources/rhythmicsetupform.cpp \
    Forms Sources/intro.cpp \
    Forms Sources/melodicsetupform.cpp \
    Forms Sources/outputdialog.cpp \
    Forms Sources/rhythmicsetupform.cpp \
    Forms Sources/intro.cpp \
    Forms Sources/melodicsetupform.cpp \
    Forms Sources/outputdialog.cpp \
    Forms Sources/rhythmicsetupform.cpp \
    Forms Sources/intro.cpp \
    Forms Sources/melodicsetupform.cpp \
    Forms Sources/outputdialog.cpp \
    Forms Sources/rhythmicsetupform.cpp \
    rhythmicsetupform.cpp \
    outputdialog.cpp \
    melodicsetupform.cpp \
    intro.cpp

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
    Forms Headers/intro.h \
    Forms Headers/melodicsetupform.h \
    Forms Headers/outputdialog.h \
    Forms Headers/rhythmicsetupform.h \
    Forms Headers/intro.h \
    Forms Headers/melodicsetupform.h \
    Forms Headers/outputdialog.h \
    Forms Headers/rhythmicsetupform.h \
    Forms Headers/intro.h \
    Forms Headers/melodicsetupform.h \
    Forms Headers/outputdialog.h \
    Forms Headers/rhythmicsetupform.h \
    pcg_uint128.hpp \
    rhythmicsetupform.h \
    outputdialog.h \
    melodicsetupform.h \
    intro.h

FORMS += \
    intro.ui \
    rhythmicsetupform.ui \
    outputdialog.ui \
    melodicsetupform.ui

RESOURCES += \
    midiheader.qrc \
    midiheadersample.qrc

DISTFILES +=
