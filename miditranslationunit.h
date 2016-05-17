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

class MidiTranslationUnit
{
    public:
        MidiTranslationUnit();
        void setTimeClock(const int _clock);
        bool setSampleHeaderAddress(const std::string &_address);
        bool setOutputFileAddress(const std::string &_address);
        bool setInputFileAddress(const std::string &_address);
        void setPulseMeasure(const PulseMeasureValidFigures _pulseMeasure);
        void setPulseNumber(const int _pulseNumber);
        void translateToMidi(const std::vector<Note> &_input);
        bool translateToNote();
        void writeToFile();

    private:
        unsigned long maxValueVlq(const int _byteNumber);
        int byteNumberVlq(const unsigned long _value);
        std::vector<unsigned char> dataToVlq(unsigned long _value);
        std::vector<unsigned char> formatTimeValue(float _value);
        void writeToHeader();
        void writeData();
        void writeTimeSignature();
        void writeTimeClock();
        std::fstream sampleHeader;
        std::fstream outputFile;
        std::fstream inputFile;
        std::vector<unsigned char> outputData;
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
