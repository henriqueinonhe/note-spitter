#ifndef NUMERICCONVERTER_H
#define NUMERICCONVERTER_H

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <math.h>
#include <limits>

#ifndef NUL
#define NUL 0
#endif

namespace NumCon
{
    enum LetterCase
    {
     UPPERCASE,
     LOWERCASE
    };

    //Declarations

    int charToInt(char _char, int _base = 10);
    char intToChar(int _int, int _base = 10);
    std::string intToStr(int _int, int _base = 10);
    int strToInt(std::string _str, int _base = 10);
    bool isDigit(char _char, int _base = 10);
    bool isNumber(std::string _str);
    int countDigit(int _int);
    int countDigit(std::string _str);



}

//Definitions

int NumCon::charToInt(char _char, int _base, LetterCase _case)
{
    /* Converts the target char to int
     * in the given base, from 2 up to 36.
     * It does not support negative integers convertion.
     * If the convertion fails it returns -1*/

    /* First it checks if the target character
     * is really a digit in the given base*/
    if(isDigit(_char, _base))
    {
        if('0' <= _char && _char <= '9') //From 0 up to 9
        {
            return _char - '0';
        }
        else if('A' <= _char && _char <= 'Z') //From A up to Z
        {
            return _char - 'A' + 11; //If _char == A the value is 0 + 11 and so on
        }
        else if('a' <= _char && _char <= 'z') //From a up to z
        {
            return _char - 'a' + 11;
        }
    }
    else return -1;
}

char NumCon::intToChar(int _int, int _base)
{
    /* Converts target integer to char taking into
     * consideration the lettter case.
     * Supports convertions from base 2 up to 36.
     * If conversion is not supported returns NUL (0).*/

    /* First it checks if the base is
     * in the base range and the integer
     * is less than the base.*/
    if(2 <= _base && _base <= 36 && _int <= _base)
    {
        if(0 <= _int && _int <= 10) //Between 2 and 10
        {
            return '0' + _int;
        }
        else if(_case == UPPERCASE) //Between 10 and 36 uppercase
        {
            return 'A' + (_int - 10);
        }
        else if(_case == LOWERCASE) //Between 10 and 36 lowercase
        {
            return 'a' + (_int - 10);
        }
    }
    else
    {
        std::cout << "Conversion is not supported! Base must be betweeen 2 and 36 inclusive and the integer must be positive!\n";
        return NULL;
    }
}

std::string NumCon::intToStr(int _int, int _base)
{
    /* Converts and integer to an string in the
     * given base, which must be between
     * 2 and 36 inclusive.
     * Supports negative integers convertion.*/

    std::string _str;

    /*First it checks if the base is supported.*/
    if(2 <= _base && _base <= 36)
    {
        for(int _power = 0; _int != 0; _power++)
        {
            _str.insert(_str.begin(), _int % _base);
            _int /= _base;
        }

        return _str;
    }
    else
    {
        std::cout << "This base is not supported! Must be between 2 and 36 inclusive!\n";
        return _str;
    }
}

int NumCon::strToInt(std::string _str, int _base)
{
    /* Converts the entire string to an integer
     * in the given base.
     * Supports negative integers.
     * If it is not possible to be converted returns
     * -99999999.*/

    int _int = 0;

    /* First it checks if the given string
     * is a number in the given base.*/
    if(isNumber(_str, _base))
    {
        /* We begin in the last digit of the number.
         * We only go until the second digit, because
         * the first one could either be a digit or
         * a minus (-) sign, so we deal with the first
         * digit separetely.*/
        int _power = 0; //Power we will raise the digits

        for(auto _iterator = _str.rend(); _iterator != _str.rbegin(); _iterator++, _power++)
        {
            if('0' <= *_iterator && *_iterator <= '9')
            {
                _int += (*_iterator - '0') * pow(_base, _power);
            }
            else if('A' <= *_iterator && *_iterator <=  'Z')
            {
                _int += (*_iterator - 'A' + 10) * pow(_base, _power);
            }
            else if('a' <= *_iterator && *_iterator <= 'z')
            {
                _int += (*_iterator - 'a' + 10) * pow(_base, _power);
            }
        }

        /*Dealing with the last digit*/
        if(_str.begin() == '-')
        {
            _int *= -1;
        }
        else
        {
            if('0' <= *_iterator && *_iterator <= '9')
            {
                _int += (*_iterator - '0') * pow(_base, _power);
            }
            else if('A' <= *_iterator && *_iterator <=  'Z')
            {
                _int += (*_iterator - 'A' + 10) * pow(_base, _power);
            }
            else if('a' <= *_iterator && *_iterator <= 'z')
            {
                _int += (*_iterator - 'a' + 10) * pow(_base, _power);
            }
        }
        return _int;
    }
    else
    {
        std::cout << "Conversion failed!\n";
        return -99999999;
    }
}

bool NumCon::isDigit(char _char, int _base)
{
    /* Returns true if the character is a digit in
     * the given base and false otherwise.
     * Also base should be less or equal than 36
     * or it will return false.
     * If the parameters are out of bounds it will
     * return false */

    //There cannot be a numeric base less than 2.
    if(_base < 2)
    {
        std::cout << "Base less than two!\n";
        return false;
    }

    //Between base 2 and 10 inclusive.
    if(2 <= _base && _base <= 10)
    {
        return '0' <= _char && _char <= '0' + _base;
    }
    else if(11 <= _base && _base <= 36)
    {
        return ('0' <= _char && _char <= '9') || //Between 0 and 9
               ('A' <= _char && _char <= 'A' + (_base - 10)) || //Between A and A + (_base - 10) (up to Z)
               ('a' <= _char && _char <= 'a' + (_base - 10)); //Between a and a +(_base - 10) (up to z)
    }
    else
    {
        std::cout << "Base greater than maximum permitted (36)!\n";
        return false;
    }
}

bool NumCon::isNumber(std::string _str, int _base)
{
    /* Checks if the string only contain digits
     * in a given base and at most a minus (-) sign
     * at the beggining.
     * If so it returns true.
     * If there is any other "foreign" character in the string
     * it returns false.*/

    /* The first character receives special treatment
     * in case it is a minus sign.*/
    if(!isDigit(_str[0]) && _str[0] != '-') return false;

    for(int _index = 1; _index < _str.size(); _index++)
    {
        if(!isDigit(_str[_index], _base)) return false;
    }

    return true;
}

int NumCon::countDigit(int _int)
{
    /* Counts the number of digits in the given
     * integer, always in base 10.*/

    /* This algorithm works by repeated iteration
     * through the division by 10, until it yields
     * 0.
     * Each division "takes off" 1 digit of the number.
     * It is important to recall that the number 0
     * has one digit. */

    int _digitCounter = 0;

    do
    {
        _int /= 10;
        _digitCounter ++;
    }while(_int != 0);

    return _digitCounter;
}

int NumCon::countDigit(std::string _str)
{
    /* Counts the number of digits on a string if it is
     * a number.
     * Useful because it returns the number of digits regardless
     * if the number is positive or negative.
     * If the string doesn't hold a number returns -1;*/

    //The string must hold a number.
    if(isNumber(_str))
    {
        if(_str[0] == '-') return _str.size() - 1;
        else return _str.size();
    }
    else return -1;
}

/* Adapt to more types conversion and including limits and boundaries
 * This is very important, I need to make a revision of this and implement
 * everything carefully to prevent conversion errors and problems and etc.*/

#endif // NUMERICCONVERTER_H
