#include <iostream>
#include "utils/printer.h"

using namespace Util;
using std::cout;
using std::endl;

Printer::Printer(HMS::Client &client) : client(client) {}

void Printer::printHeader()
{
    this->clearConsole();

    // Title header
    this->printDivider();
    cout << "Hospital Management System" << endl;
    this->printDivider();

    // Error header
    int size = this->client.errorHandler.getErrorSize();
    if (size)
    {
        // Print a divider before the errors.
        this->printDivider();

        // Print each error message.
        for (int i = 0; i < size; i++)
        {
            Handler::ErrorStruct *error = this->client.errorHandler.getError(i);
            std::cout << "Warning: " << error->message << std::endl;
        }
        // Print a divider after the errors.
        this->printDivider();
        // Reset the error list.
        this->client.errorHandler.resetError();
    }
};

void Printer::printDivider()
{
    cout << "======================================" << endl;
};

void Printer::clearConsole()
{
#if defined _WIN32
    system("cls"); // Clear console for Windows.

#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear"); // Clear console for Linux.

#elif defined(__APPLE__)
    system("clear"); // Clear console for macOS.
#endif
};