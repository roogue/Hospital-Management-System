#pragma once

#include <iostream>
#include "structs/orderedLinkedList.h"

namespace Handler
{
    struct ErrorStruct
    {
        int code;
        std::string message;

        bool operator==(const ErrorStruct &other)
        {
            return code == other.code;
        };
        bool operator!=(const ErrorStruct &other)
        {
            return code != other.code;
        };
        bool operator>=(const ErrorStruct &other)
        {
            return code >= other.code;
        };
        bool operator>(const ErrorStruct &other)
        {
            return code > other.code;
        };
        bool operator<=(const ErrorStruct &other)
        {
            return code <= other.code;
        };
        bool operator<(const ErrorStruct &other)
        {
            return code < other.code;
        };
    };

    class ErrorHandler
    {
    public:
        void addError(int errorCode);
        ErrorStruct *getError(int errorCode);
        void resetError();
        int getErrorSize();

        void registerErrorMessage(int prefix, const std::string errorMessages[], int errorMessagesSize);

    private:
        OrderedLinkedList<ErrorStruct> registers;
        LinkedList<ErrorStruct> errors;
    };
}
