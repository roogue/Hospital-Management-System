#pragma once

#include <iostream>
#include "structs/orderedLinkedList.h"

using ErrorCode = int;

namespace Handler
{
    /**
     * @brief Structure to hold error information.
     */
    struct ErrorStruct
    {
        int code;            /**< Error code */
        std::string message; /**< Error message */

        /**
         * @brief Equality operator to compare two error structures.
         * @param other The other error structure to compare.
         * @return True if the error codes are equal, false otherwise.
         */
        bool operator==(const ErrorStruct &other)
        {
            return code == other.code;
        };

        /**
         * @brief Inequality operator to compare two error structures.
         * @param other The other error structure to compare.
         * @return True if the error codes are not equal, false otherwise.
         */
        bool operator!=(const ErrorStruct &other)
        {
            return code != other.code;
        };

        /**
         * @brief Greater than or equal operator to compare two error structures.
         * @param other The other error structure to compare.
         * @return True if this error code is greater than or equal to the other, false otherwise.
         */
        bool operator>=(const ErrorStruct &other)
        {
            return code >= other.code;
        };

        /**
         * @brief Greater than operator to compare two error structures.
         * @param other The other error structure to compare.
         * @return True if this error code is greater than the other, false otherwise.
         */
        bool operator>(const ErrorStruct &other)
        {
            return code > other.code;
        };

        /**
         * @brief Less than or equal operator to compare two error structures.
         * @param other The other error structure to compare.
         * @return True if this error code is less than or equal to the other, false otherwise.
         */
        bool operator<=(const ErrorStruct &other)
        {
            return code <= other.code;
        };

        /**
         * @brief Less than operator to compare two error structures.
         * @param other The other error structure to compare.
         * @return True if this error code is less than the other, false otherwise.
         */
        bool operator<(const ErrorStruct &other)
        {
            return code < other.code;
        };
    };

    /**
     * @brief Class to handle and manage errors in the system.
     */
    class ErrorHandler
    {
    public:
        /**
         * @brief Adds an error to the error list.
         * @param errorCode The error code to add.
         */
        void addError(int errorCode);

        /**
         * @brief Retrieves an error by its code.
         * @param errorCode The error code to retrieve.
         * @return Pointer to the error structure, or nullptr if not found.
         */
        ErrorStruct *getError(int errorCode);

        /**
         * @brief Resets the error list, clearing all errors.
         */
        void resetError();

        /**
         * @brief Gets the number of errors currently stored.
         * @return The number of errors.
         */
        int getErrorSize();

        /**
         * @brief Registers error messages with a specific prefix.
         * @param prefix The prefix for the error codes.
         * @param errorMessages Array of error messages.
         * @param errorMessagesSize The size of the error messages array.
         */
        void registerErrorMessage(int prefix, const std::string errorMessages[], int errorMessagesSize);

    private:
        OrderedLinkedList<ErrorStruct> registers; /**< List of registered error messages */
        LinkedList<ErrorStruct> errors;           /**< List of current errors */
    };
}
