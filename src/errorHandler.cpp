#include <iostream>
#include "handlers/errorHandler.h"
#include "utils/printer.h"

using namespace Handler;

void ErrorHandler::addError(int errorCode)
{
    ErrorStruct searchStruct = {errorCode}; // There's no need the error messages
    ErrorStruct *error = this->registers.getData(searchStruct);

    this->errors.addNode(*error);
};

ErrorStruct *ErrorHandler::getError(int errorCode)
{
    return this->errors.getData(errorCode);
}

void ErrorHandler::resetError()
{
    this->errors.reset();
};

int ErrorHandler::getErrorSize()
{
    return this->errors.getSize();
};

void ErrorHandler::registerErrorMessage(int prefix, const std::string errorMessages[], int errorMessagesSize)
{
    for (int i = 0; i < errorMessagesSize; i++)
    {
        int code = prefix + i;
        ErrorStruct error = {code, errorMessages[i]};
        this->registers.addNode(error);
    }
}