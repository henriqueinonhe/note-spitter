QT += core
QT -= gui

CONFIG += c++11

TARGET = ProjetoMusica
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    note.cpp \
    rhythmicsetup.cpp \
    melodicsetup.cpp \
    melodicsolfege.cpp \
    miditranslationunit.cpp

HEADERS += \
    note.h \
    rhythmicsetup.h \
    melodicsetup.h \
    melodicsolfege.h \
    pcg_random.hpp \
    pcg_extras.hpp \
    miditranslationunit.h \
    musicenums.h \
    numericconverter.hpp
