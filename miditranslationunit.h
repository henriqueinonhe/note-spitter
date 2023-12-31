#ifndef MIDITRANSLATIONUNIT_H
#define MIDITRANSLATIONUNIT_H

#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

#include "musicenums.h"
#include "note.h"
#include "numericconverter.hpp"

#include <QFile>
#include <QTextStream>
#include <QDataStream>

class MidiTranslationUnit
{


    public:
        MidiTranslationUnit();
        void setTimeClock(const int _clock);
        bool setSampleHeaderAddress(const QString &_address);
        bool setOutputFileAddress(const QString &_address);
        bool setInputFileAddress(const QString &_address);
        void setPulseMeasure(const PulseMeasureValidFigures _pulseMeasure);
        void setPulseNumber(const int _pulseNumber);
        void setAttributesFromInput();
        void translateToMidi(const std::vector<Note> &_input);
        bool translateToNote(std::vector<Note> &_output);
        void writeToFile();
        void readToInput();

    private:
        unsigned long maxValueVlq(const int _byteNumber);
        int byteNumberVlq(const unsigned long _value);
        int byteNumberVlq(const std::vector<unsigned char> &_vector, const int _beg);
        std::vector<unsigned char> dataToVlq(unsigned long _value);
        int vlqToInt(const std::vector<unsigned char> &_vector, const int _beg);
        std::vector<unsigned char> formatTimeValue(float _value);
        double unformatTimeValuePitched(const std::vector<unsigned char> &_vector, const int _beg);
        double unformatTimeValueRest(const std::vector<unsigned char> &_vector, const int _beg);
        void writeToHeader();
        void writeData();
        void writeTimeSignature();
        void writeTimeClock();
        void readTimeSignature();
        void readTimeClock();
        QFile sampleHeader;
        QFile outputFile;
        QFile inputFile;
        std::vector<unsigned char> outputData;
        std::vector<unsigned char> inputData;
        int pulseNumber;
        PulseMeasureValidFigures pulseMeasure;
        int timeClock;

    //Note: VLQ = Variable Lenght Quantity
    //MSBit (0x80) indicates whether another byte regarding the same
    //quantity follows, so the maximum value that any byte can attain
    //if 0x7f, anything over that indicates that the value attained is
    //value - 0x7f indicating that another byte follows

};

#endif // MIDITRANSLATIONUNIT_H
