#ifndef NUMERICCONVERSOR_H
#define NUMERICCONVERSOR_H

#include <vector>
#include <string>
#include <array>
#include <iostream>

#ifndef NUL
#define NUL 0
#endif

typedef class NumericConversor NumCon;

class NumericConversor
{
    public:
        enum LetterCase
        {
            UPPERCASE,
            LOWERCASE
        };

        static int charToInt(char _char, int _base = 10);
        static char intToChar(int _int, int _base = 10);
        static std::string intToStr(int _int, int _base = 10);
        static int strToInt(std::string _str, int _base = 10);
        static bool isDigit(char _char, int _base = 10);
        static bool isNumber(std::string _str);
        static int countDigit(int _int);


    private:

};

#endif // NUMERICCONVERSOR_H
