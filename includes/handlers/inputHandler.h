#pragma once

#include <iostream>

namespace Handler
{
    struct Date
    {
        int day;
        int month;
        int year;

        bool operator==(const Date &other);
        bool operator!=(const Date &other);
        bool operator<(const Date &other);
        bool operator<=(const Date &other);
        bool operator>(const Date &other);
        bool operator>=(const Date &other);

        std::string getFormattedDate();
    };

    extern const int InputErrorPrefix;

    enum InputError
    {
        NO_INPUT_ERR,
        STRING_TOO_FEW,
        STRING_TOO_LARGE,
        INT_TOO_SMALL,
        INT_TOO_LARGE,
        INT_INVALID,
        DATE_INVALID,
    };
    extern const std::string InputErrorMessage[];
    extern const int InputErrorMessageSize;

    extern const int MAX_STRING;
    extern const int MAX_INT;

    class InputHandler
    {
    public:
        InputError getString(std::string &str, int limitMin = 1, int limitMax = MAX_STRING);

        InputError getInt(int &num, int limitMin = 1, int limitMax = MAX_INT);

        InputError getDate(Date &date);

    private:
        bool isLeapYear(int year);
        bool isValidDate(int day, int month, int year);

        void clearBuffer();
    };
}