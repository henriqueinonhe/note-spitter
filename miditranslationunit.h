#ifndef MIDITRANSLATIONUNIT_H
#define MIDITRANSLATIONUNIT_H

#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

#include "musicenums.h"
#include "note.h"

class MidiTranslationUnit
{
    public:
        MidiTranslationUnit();
        void setTimeClock(int _clock);
        bool setSampleHeaderAddress(const std::string &_address);
        bool setOutputFileAddress(const std::string &_address);
        bool setInputFileAddress(const std::string &_address);
        void setPulseMeasure(PulseMeasureValidFigures _pulseMeasure);
        void setPulseNumber(int _pulseNumber);
        void translateToMidi(std::vector<Note> _input);
        bool translateToNote();
        void writeToFile();

    private:
        unsigned long maxValueVlq(int _byteNumber);
        int byteNumberVlq(unsigned long _value);
        std::vector<unsigned char> dataToVlq(unsigned long _value);
        std::vector<unsigned char> formatTimeValue(float _value);
        std::vector<unsigned char> convertByteNumber(unsigned int _value);
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
