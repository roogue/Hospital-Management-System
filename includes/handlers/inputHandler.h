#pragma once

#include "handlers/errorHandler.h"
#include <iostream>

namespace Handler
{
    /**
     * @brief Structure to represent a date.
     */
    struct Date
    {
        int day;   /**< Day of the month */
        int month; /**< Month of the year */
        int year;  /**< Year */

        /**
         * @brief Equality operator to compare two dates.
         * @param other The other date to compare.
         * @return True if the dates are equal, false otherwise.
         */
        bool operator==(const Date &other);

        /**
         * @brief Inequality operator to compare two dates.
         * @param other The other date to compare.
         * @return True if the dates are not equal, false otherwise.
         */
        bool operator!=(const Date &other);

        /**
         * @brief Less than operator to compare two dates.
         * @param other The other date to compare.
         * @return True if this date is earlier than the other, false otherwise.
         */
        bool operator<(const Date &other);

        /**
         * @brief Less than or equal operator to compare two dates.
         * @param other The other date to compare.
         * @return True if this date is earlier than or the same as the other, false otherwise.
         */
        bool operator<=(const Date &other);

        /**
         * @brief Greater than operator to compare two dates.
         * @param other The other date to compare.
         * @return True if this date is later than the other, false otherwise.
         */
        bool operator>(const Date &other);

        /**
         * @brief Greater than or equal operator to compare two dates.
         * @param other The other date to compare.
         * @return True if this date is later than or the same as the other, false otherwise.
         */
        bool operator>=(const Date &other);

        /**
         * @brief Gets the date as a formatted string.
         * @return The formatted date string.
         */
        std::string getFormattedDate();
    };

    extern const int InputErrorPrefix; /**< Prefix for input error codes */

    /**
     * @brief Enumeration of input error codes.
     */
    enum InputError
    {
        NO_INPUT_ERR,     /**< No error */
        STRING_TOO_FEW,   /**< String input is too short */
        STRING_TOO_LARGE, /**< String input is too long */
        INT_TOO_SMALL,    /**< Integer input is too small */
        INT_TOO_LARGE,    /**< Integer input is too large */
        INT_INVALID,      /**< Integer input is invalid */
        DATE_INVALID      /**< Date input is invalid */
    };

    extern const std::string InputErrorMessage[]; /**< Array of input error messages */
    extern const int InputErrorMessageSize;       /**< Size of the input error message array */

    extern const int MAX_STRING; /**< Maximum length for string inputs */
    extern const int MAX_INT;    /**< Maximum value for integer inputs */

    /**
     * @brief Class to handle input operations.
     */
    class InputHandler
    {
    public:
        /**
         * @brief Gets a string input from the user.
         * @param str Reference to the string to store the input.
         * @param limitMin Minimum length of the string.
         * @param limitMax Maximum length of the string.
         * @return Error code indicating success or type of input error.
         */
        ErrorCode getString(std::string &str, int limitMin = 1, int limitMax = MAX_STRING);

        /**
         * @brief Gets an integer input from the user.
         * @param num Reference to the integer to store the input.
         * @param limitMin Minimum value of the integer.
         * @param limitMax Maximum value of the integer.
         * @return Error code indicating success or type of input error.
         */
        ErrorCode getInt(int &num, int limitMin = 1, int limitMax = MAX_INT);

        /**
         * @brief Gets a date input from the user.
         * @param date Reference to the date structure to store the input.
         * @return Error code indicating success or type of input error.
         */
        ErrorCode getDate(Date &date);

        /**
         * @brief Pauses the program until the user presses enter.
         */
        void pause();

        /**
         * @brief Gets the error code corresponding to a specific input error.
         * @param error The input error.
         * @return The corresponding error code.
         */
        ErrorCode getErrorCode(InputError error);

        /**
         * @brief Gets the error code indicating no error.
         * @return The error code for no error.
         */
        ErrorCode noErrorCode();

    private:
        /**
         * @brief Checks if a year is a leap year.
         * @param year The year to check.
         * @return True if the year is a leap year, false otherwise.
         */
        bool isLeapYear(int year);

        /**
         * @brief Validates a date.
         * @param day The day of the month.
         * @param month The month of the year.
         * @param year The year.
         * @return True if the date is valid, false otherwise.
         */
        bool isValidDate(int day, int month, int year);

        /**
         * @brief Clears the input buffer.
         */
        void clearBuffer();
    };
}
