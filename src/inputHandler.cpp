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
    // Check if both dates have the same day, month and year
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
    // Compare year first, return true if this year is greater
    if (this->year > other.year)
    {
        return true;
    }
    // If years are equal, compare month
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
    // If months are equal, compare day
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
    // Convert day, month, and year to strings
    std::string dayStr = to_string(this->day);
    std::string monthStr = to_string(this->month);
    std::string yearStr = to_string(this->year);
    // Format date as DD/MM/YYYY, adding leading zeroes if necessary
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
    // Ensure limitMax is greater than or equal to limitMin
    if (limitMax < limitMin)
    {
        throw std::out_of_range("Limit min must be less than limit max.");
    }

    // Get input string from the user
    std::getline(std::cin, str);

    // Check if the length of the string is less than the minimum limit
    if (str.length() < limitMin)
    {
        return getErrorCode(STRING_TOO_FEW);
    }

    // Check if the length of the string is greater than the maximum limit
    if (str.length() > limitMax)
    {
        // Truncate the string to the maximum limit
        str = str.substr(0, limitMax);
    }

    return getErrorCode(NO_INPUT_ERR);
}

ErrorCode InputHandler::getInt(int &num, int limitMin, int limitMax)
{
    // Ensure limitMax is greater than or equal to limitMin
    if (limitMax < limitMin)
    {
        throw std::out_of_range("Limit min must be less than limit max.");
    }

    // Get input integer from the user
    std::cin >> num;

    // Check if input stream is invalid input
    if (std::cin.bad())
    {
        this->clearBuffer();
        return getErrorCode(INT_INVALID);
    }

    // Clear the input buffer to handle any remaining input
    this->clearBuffer();

    // Check if the integer is less than the minimum limit
    if (num < limitMin)
    {
        return getErrorCode(INT_TOO_SMALL);
    }

    // Check if the integer is greater than the maximum limit
    if (num > limitMax)
    {
        return getErrorCode(INT_TOO_LARGE);
    }

    return getErrorCode(NO_INPUT_ERR);
};

ErrorCode InputHandler::getDate(Date &date)
{
    // Get input date string from the user
    std::string input;
    std::getline(std::cin, input);

    char delimiter;
    // Use stringstream to analyze the date in the format DD/MM/YYYY
    std::istringstream dateStream(input);
    if (dateStream >> date.day >> delimiter >> date.month >> delimiter >> date.year)
    {
        // Check if the analyzed date is valid
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
    // Check if the year is a leap year
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
};

bool InputHandler::isValidDate(int day, int month, int year)
{
    // Check if the year is valid
    if (year < 1900 || month < 1 || month > 12 || day < 1)
    {
        return false;
    }

    // Days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check if the month is February and the year is a leap year
    if (month == 2 && isLeapYear(year))
    {
        return day <= 29;
    }

    // Check if the day is within the valid range for the month
    return day <= daysInMonth[month - 1];
};

void InputHandler::pause()
{
    std::string str;
    this->getString(str);
}

ErrorCode InputHandler::getErrorCode(InputError error)
{
    // Return the error code corresponding to the input error
    return (InputErrorPrefix + error);
}

ErrorCode InputHandler::noErrorCode()
{
    // Return the no error code
    return (InputErrorPrefix + InputError::NO_INPUT_ERR);
}

// Method to clear the input buffer
void InputHandler::clearBuffer()
{
    std::cin.clear();                                                   // clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any remaining input
};
