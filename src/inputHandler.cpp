#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <string>
#include "handlers/inputHandler.h"
#include "structs/linkedList.h"

using namespace Handler;

bool Date::operator==(const Date &other)
{
    return (this->day == other.day) &&
           (this->month == other.month) && 
           (this->year == other.year);
};
bool Date::operator!=(const Date &other)
{
    return !(*this == other);
};
bool Date::operator<(const Date &other)
{
    if (this->year > other.year)
    {
        return true;
    }
    if (this->year < other.year)
    {
        return false;
    }
    if (this->month > other.month)
    {
        return true;
    }
    if (this->month < other.month)
    {
        return false;
    }

    return this->day > other.day;
};
bool Date::operator<=(const Date &other)
{
    return (*this < other) || (*this == other);
};
bool Date::operator>(const Date &other)
{
    return !(*this <= other);
};
bool Date::operator>=(const Date &other)
{
    return !(*this < other);
};

std::string Date::getFormattedDate()
{
    using std::to_string;
    std::string dayStr = to_string(this->day);
    std::string monthStr = to_string(this->month);
    std::string yearStr = to_string(this->year);
    return (this->day < 10 ? "0" + dayStr : dayStr) + "/" + (this->month < 10 ? "0" + monthStr : monthStr) + "/" + (this->year == 0 ? "0000" : yearStr);
};

const std::string Handler::InputErrorMessage[] = {
    "No error occurred",
    "The input string is too few",
    "The input string is too large",
    "The input integer is too small",
    "The input integer is too large",
    "The input integer is invalid",
    "The input date is invalid"};
const int Handler::InputErrorMessageSize = sizeof(Handler::InputErrorMessage) / sizeof(Handler::InputErrorMessage[0]);
const int Handler::InputErrorPrefix = 0;

const int Handler::MAX_STRING = 200;
const int Handler::MAX_INT = INT_MAX;

ErrorCode InputHandler::getString(
    std::string &str,
    int limitMin,
    int limitMax)
{
    if (limitMax < limitMin)
    {
        throw std::out_of_range("Limit min must be less than limit max.");
    }

    std::getline(std::cin, str);

    if (str.length() < limitMin)
    {
        return getErrorCode(STRING_TOO_FEW);
    }

    if (str.length() > limitMax)
    {
        str = str.substr(0, limitMax);
    }

    return getErrorCode(NO_INPUT_ERR);
}

ErrorCode InputHandler::getInt(int &num, int limitMin, int limitMax)
{
    if (limitMax < limitMin)
    {
        throw std::out_of_range("Limit min must be less than limit max.");
    }

    std::cin >> num;

    if (std::cin.bad())
    {
        this->clearBuffer();
        return getErrorCode(INT_INVALID);
    }

    this->clearBuffer();

    if (num < limitMin)
    {
        return getErrorCode(INT_TOO_SMALL);
    }

    if (num > limitMax)
    {
        return getErrorCode(INT_TOO_LARGE);
    }

    return getErrorCode(NO_INPUT_ERR);
};

ErrorCode InputHandler::getDate(Date &date)
{
    std::string input;
    std::getline(std::cin, input);

    char delimiter;
    std::istringstream dateStream(input);
    if (dateStream >> date.day >> delimiter >> date.month >> delimiter >> date.year)
    {
        if (!this->isValidDate(date.day, date.month, date.year))
        {
            return getErrorCode(DATE_INVALID);
        }

        return getErrorCode(NO_INPUT_ERR);
    }

    return getErrorCode(DATE_INVALID);
};

bool InputHandler::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
};
bool InputHandler::isValidDate(int day, int month, int year)
{
    if (year < 1900 || month < 1 || month > 12 || day < 1)
    {
        return false;
    }

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
    {
        return day <= 29;
    }

    return day <= daysInMonth[month - 1];
};

ErrorCode InputHandler::getErrorCode(InputError error)
{
    return (InputErrorPrefix + error);
}

ErrorCode InputHandler::noErrorCode()
{
    return (InputErrorPrefix + InputError::NO_INPUT_ERR);
}

void InputHandler::clearBuffer()
{
    std::cin.clear(); // clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};