#ifndef NUMERICCONVERTER_HPP
#define NUMERICCONVERTER_HPP

#include <vector>
#include <string>
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
    char intToChar(int _int, int _base = 10, LetterCase _case = LOWERCASE);
    std::string intToStr(long long _int, int _base = 10, LetterCase _case = LOWERCASE);
    long long strToInt(std::string _str, int _base = 10);
    bool isDigit(char _char, int _base = 10);
    bool isNumber(std::string _str, int _base = 10);
    bool isNumber(std::vector<char> _vector, int _base = 10);
    int countDigit(long long _long, int _base = 10);
    int countDigit(std::string _str, int _base = 36);
    unsigned long long maxValue(int _base, int _digitNum);
    std::vector<int> convertToVector(long long _int, int _base, int _digitNum);
    std::vector<char> convertToVector(long long _int, int _base, int _digitNum, char);
    long long convertFromVector(std::vector<int> _vector, int _base, unsigned int _beg = 0, int _digitNum = -1);
    long long convertFromVector(std::vector<char> _vector, int _base, unsigned  int _beg = 0, int _digitNum  = -1);
    long long convertFromVector(std::vector<unsigned char> _vector, int _base, unsigned int _beg = 0, int _digitNum  = -1);
}
//Definitions

inline int NumCon::charToInt(char _char, int _base)
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

    return -1;
}

inline char NumCon::intToChar(int _int, int _base, LetterCase _case)
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
        std::cout << "Conversion is not supported! Base must be betweeen 2 and 36 inclusive.\n"
                     "The integer must be greater than the base!\n";
        return NUL;
    }

    return NUL;
}

inline std::string NumCon::intToStr(long long _int, int _base, LetterCase _case)
{
    /* Converts and integer to an string in the
     * given base, which must be between
     * 2 and 36 inclusive.
     * Supports negative integers convertion.*/

    std::string _str;

    /*First it checks if the base is supported.*/
    if(2 <= _base && _base <= 36)
    {
        /* If the integer is zero it is straightforward
         * moreover zer is the only integer for which the following
         * algorithm fails. */
        if(_int == 0) _str.push_back('0');

        for(int _power = 0; _int != 0; _power++)
        {
            _str.insert(_str.begin(), intToChar(_int % _base, _base, _case));
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

inline long long NumCon::strToInt(std::string _str, int _base)
{
    /* Converts the entire string to an integer
     * in the given base.
     * Supports negative integers.
     * If it is not possible to be converted returns
     * LLONG_MAX.
     * If the convertion makes the number overflow
     * it also returns LLONG_MAX. */

    long long _int = 0;
    long long _previousInt = 0; //Overflow check

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
            if(_previousInt > _int)
            {
                std::cout << "Overflow!\n";
                return LLONG_MAX;
            }
            else _previousInt = _int;
        }

        /*Dealing with the last digit*/
        if(_str.front() == '-')
        {
            _int *= -1;
        }
        else
        {
            if('0' <= _str.front() && _str.front() <= '9')
            {
                _int += (_str.front() - '0') * pow(_base, _power);
            }
            else if('A' <= _str.front() && _str.front() <=  'Z')
            {
                _int += (_str.front() - 'A' + 10) * pow(_base, _power);
            }
            else if('a' <= _str.front() && _str.front() <= 'z')
            {
                _int += (_str.front() - 'a' + 10) * pow(_base, _power);
            }
        }
        return _int;
    }
    else
    {
        std::cout << "Conversion failed!\n";
        return LLONG_MAX;
    }
}

inline bool NumCon::isDigit(char _char, int _base)
{
    /* Returns true if the character is a digit in
     * the given base and false otherwise.
     * Also base should be less or equal than 36
     * or it will return false.
     * If the parameters are out of bounds it will
     * return false */

    //There cannot be a numeric base less than 2.
    if(_base < 2 || _base > 36)
    {
        std::cout << "Base must be between 2 and 36 inclusive!";
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

inline bool NumCon::isNumber(std::string _str, int _base)
{
    /* Checks if the string only contain digits
     * in a given base and at most a minus (-) sign
     * at the beggining.
     * If so it returns true.
     * If there is any other "foreign" character in the string
     * it returns false.
     * If the string is empty returns false. */

    if(_str.empty()) //Checks if the string is empty
    {
        std::cout << "The string is empty!\n";
        return false;
    }
    /* The first character receives special treatment
     * in case it is a minus sign.*/
    else if(!isDigit(_str[0], _base) && _str[0] != '-') return false;

    for(unsigned int _index = 1; _index < _str.size(); _index++)
    {
        if(!isDigit(_str[_index], _base)) return false;
    }

    return true;
}

inline bool NumCon::isNumber(std::vector<char> _vector, int _base)
{
    /* Checks if the vector only contain digits
     * in a given base and at most a minus (-) sign
     * at the beggining.
     * If so it returns true.
     * If there is any other "foreign" character in the string
     * it returns false.
     * If the vector is empty returns false. */

    if(_vector.empty()) //Checks if the vector is empty
    {
        std::cout << "The vector is empty!\n";
    }
    /* The first character receives special treatment
     * in case it is a minus sign.*/
    else if(!isDigit(_vector[0], _base) && _vector[0] != '-') return false;

    for(int unsigned _index = 1; _index < _vector.size(); _index++)
    {
        if(!isDigit(_vector[_index], _base)) return false;
    }

    return true;
}

inline int NumCon::countDigit(long long _long, int _base)
{
    /* Counts the number of digits in the given
     * integer, in ANY base.*/

    /* This algorithm works by repeated iteration
     * through the division by base, until it yields
     * 0.
     * Each division "takes off" 1 digit of the number.
     * It is important to recall that the number 0
     * has one digit. */

    int _digitCounter = 0;

    do
    {
        _long /= _base;
        _digitCounter ++;
    }while(_long != 0);

    return _digitCounter;
}

inline int NumCon::countDigit(std::string _str, int _base)
{
    /* Counts the number of digits on a string if it is
     * a number.
     * Useful because it returns the number of digits regardless
     * if the number is positive or negative.
     * If the string doesn't hold a number returns -1;*/

    //The string must hold a number.
    if(isNumber(_str, _base))
    {
        if(_str[0] == '-') return _str.size() - 1;
        else return _str.size();
    }
    else return -1;
}

inline unsigned long long NumCon::maxValue(int _base, int _digitNum)
{
    /* Returns the max absolute value possible for
     * a given number of digits in any base. */

    return pow(_base, _digitNum) - 1;
}

inline std::vector<int> NumCon::convertToVector(long long _int, int _base, int _digitNum)
{
    /* This function converts _int to a vector where each
     * digit occupies a different element of the vector in the
     * given base.
     * This function is mainly used to convert a number
     * to some base to be used in some kind of codification
     * like hexadecimal.
     * The _digitNum parameter defines how many spaces
     * in the vector are gonna be used and also serves as
     * a security measure, because if the this number is less than
     * what is necessary the function returns a vector
     * with 0's only. */

    std::vector<int> _vector(_digitNum, 0);

    if(countDigit(_int, _base) <= _digitNum)
    {
        for(auto _iterator = _vector.rbegin(); _int != 0; _iterator++)
        {
            *_iterator = _int % _base;
            _int /= _base;
        }

        return _vector;
    }
    else
    {
        std::cout << "The numer of digits requested is not enough to hold this number in the given base!\n";
        return _vector;
    }
}

inline std::vector<char> NumCon::convertToVector(long long _int, int _base, int _digitNum, char)
{
    /* This function converts _int to a vector where each
     * digit occupies a different element of the vector in the
     * given base.
     * This function is mainly used to convert a number
     * to some base to be used in some kind of codification
     * like hexadecimal.
     * The _digitNum parameter defines how many spaces
     * in the vector are gonna be used and also serves as
     * a security measure, because if the this number is less than
     * what is necessary the function returns a vector
     * with 0's only.
     * This version of the function is designed to work with char vectors. */

    std::vector<char> _vector(_digitNum, 0);

    if(countDigit(_int, _base) <= _digitNum)
    {
        for(auto _iterator = _vector.rbegin(); _int != 0; _iterator++)
        {
            *_iterator = _int % _base;
            _int /= _base;
        }

        return _vector;
    }
    else
    {
        std::cout << "The numer of digits requested is not enough to hold this number in the given base!\n";
        return _vector;
    }
}

inline long long NumCon::convertFromVector(std::vector<int> _vector, int _base, unsigned int _beg, int _digitNum)
{
    /* Converts the numbers in given vector and base
     * to an integer (long long) using _digitNum digits
     * from _beg position in the vector.
     * If _digitNum = -1 it goes until the end of the vector.
     * Any base is supported.
     * If the conversion makes the long long overflow it returns
     * LLONG_MAX */

    long long _int = 0;
    long long _previousInt = 0;
    int _power = 0;

    /* Checking for _beg (cannot be greater than vector size)
     * and _digitNum (cannot be greater than vector size also). */
    if((_beg + _digitNum - 1) > _vector.size())
    {
        std::cout << "Beginning or End (_digitNum) position is out of bounds!\n";
        return LLONG_MAX;
    }
    if(_digitNum < 1)
    {
        std::cout << "Number of digits read must be at least equal to 1!\n";
        return LLONG_MAX;
    }

    if(_digitNum == - 1) _digitNum = _vector.size() - _beg;
    auto _adjustedRBegin = _vector.rbegin() + (_vector.size() - (_beg + _digitNum));
    auto _adjustedREnd = _vector.rend() - _beg;

    for(auto _iterator = _adjustedRBegin; _iterator != _adjustedREnd; _iterator++, _power++)
    {
        //Checking if the base is respected
        if(*_iterator >= _base)
        {
            std::cout << "There is a number which surpasses the given base!\n";
            return LLONG_MAX;
        }

        _int += *_iterator * pow(_base, _power);

        if(_previousInt > _int)
        {
            std::cout << "Overflow!\n";
            return LLONG_MAX;
        }
        else
        {
            _previousInt = _int;
        }
    }

    return _int;
}

inline long long NumCon::convertFromVector(std::vector<char> _vector, int _base, unsigned int _beg, int _digitNum)
{
    /* Converts the numbers in given vector and base
     * to an integer (long long) using _digitNum digits
     * from _beg position in the vector.
     * If _digitNum = -1 it goes until the end of the vector.
     * Any base is supported.
     * If the conversion makes the long long overflow it returns
     * LLONG_MAX */

    long long _int = 0;
    long long _previousInt = 0;
    int _power = 0;

    /* Checking for _beg (cannot be greater than vector size)
     * and _digitNum (cannot be greater than vector size also). */
    if((_beg + _digitNum - 1) > _vector.size())
    {
        std::cout << "Beginning or End (_digitNum) position is out of bounds!\n";
        return LLONG_MAX;
    }
    if(_digitNum < 1)
    {
        std::cout << "Number of digits read must be at least equal to 1!\n";
        return LLONG_MAX;
    }

    if(_digitNum == - 1) _digitNum = _vector.size() - _beg;
    auto _adjustedRBegin = _vector.rbegin() + (_vector.size() - (_beg + _digitNum));
    auto _adjustedREnd = _vector.rend() - _beg;

    for(auto _iterator = _adjustedRBegin; _iterator != _adjustedREnd; _iterator++, _power++)
    {
        //Checking if the base is respected
        if(*_iterator >= _base)
        {
            std::cout << "There is a number which surpasses the given base!\n";
            return LLONG_MAX;
        }

        _int += (unsigned char)(*_iterator) * pow(_base, _power);

        if(_previousInt > _int)
        {
            std::cout << "Overflow!\n";
            return LLONG_MAX;
        }
        else
        {
            _previousInt = _int;
        }
    }

    return _int;
}

inline long long NumCon::convertFromVector(std::vector<unsigned char> _vector, int _base, unsigned int _beg, int _digitNum)
{
    /* Converts the numbers in given vector and base
     * to an integer (long long) using _digitNum digits
     * from _beg position in the vector.
     * If _digitNum = -1 it goes until the end of the vector.
     * Any base is supported.
     * If the conversion makes the long long overflow it returns
     * LLONG_MAX */

    long long _int = 0;
    long long _previousInt = 0;
    int _power = 0;

    /* Checking for _beg (cannot be greater than vector size)
     * and _digitNum (cannot be greater than vector size also). */
    if((_beg + _digitNum - 1) > _vector.size())
    {
        std::cout << "Beginning or End (_digitNum) position is out of bounds!\n";
        return LLONG_MAX;
    }
    if(_digitNum < 1)
    {
        std::cout << "Number of digits read must be at least equal to 1!\n";
        return LLONG_MAX;
    }

    if(_digitNum == - 1) _digitNum = _vector.size() - _beg;
    auto _adjustedRBegin = _vector.rbegin() + (_vector.size() - (_beg + _digitNum));
    auto _adjustedREnd = _vector.rend() - _beg;

    for(auto _iterator = _adjustedRBegin; _iterator != _adjustedREnd; _iterator++, _power++)
    {
        //Checking if the base is respected
        if(*_iterator >= _base)
        {
            std::cout << "There is a number which surpasses the given base!\n";
            return LLONG_MAX;
        }

        _int += (unsigned char)(*_iterator) * pow(_base, _power);

        if(_previousInt > _int)
        {
            std::cout << "Overflow!\n";
            return LLONG_MAX;
        }
        else
        {
            _previousInt = _int;
        }
    }

    return _int;
}

#endif // NUMERICCONVERTER_HPP
