#include <iostream>
#include "handlers/errorHandler.h"
#include "utils/printer.h"

using namespace Handler;

void ErrorHandler::addError(int errorCode)
{
    // Creates a search structure with the given error code
    ErrorStruct searchStruct = {errorCode}; // There's no need the error messages

    // Retrieve the error message corresponding to the error code
    ErrorStruct *error = this->registers.getData(searchStruct);

    // Add the retrieved error to the error list
    this->errors.addNode(*error);
};

ErrorStruct *ErrorHandler::getError(int errorCode)
{
    // Retrieve the error message corresponding to the error code from the errors list
    return this->errors.getData(errorCode);
}

void ErrorHandler::resetError()
{
    // Reset the errors list, removing all stored errors.
    this->errors.reset();
};

int ErrorHandler::getErrorSize()
{
    // Get and return the size of the errors list.
    return this->errors.getSize();
};

void ErrorHandler::registerErrorMessage(int prefix, const std::string errorMessages[], int errorMessagesSize)
{
    // Loop through the array of error messages.
    for (int i = 0; i < errorMessagesSize; i++)
    {
        // Generate the error code by adding the prefix and the current index.
        int code = prefix + i;

        // Create an error structure with the generated error code and the corresponding error message.
        ErrorStruct error = {code, errorMessages[i]};

        // Add the error structure to the registers list.
        this->registers.addNode(error);
    }
}
