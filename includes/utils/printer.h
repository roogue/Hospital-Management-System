#pragma once

#include <iostream>
#include "cores/client.h"

namespace Util
{
    /**
     * @brief Class responsible for printing various elements to the console.
     */
    class Printer
    {
    public:
        /**
         * @brief Constructs a Printer with a reference to a client.
         * @param client Reference to the client.
         */
        Printer(HMS::Client &client);

        /**
         * @brief Clear console and prints the header section to the console.
         */
        void printHeader();

        /**
         * @brief Prints a divider line to the console.
         */
        void printDivider();

        /**
         * @brief Clears the console screen.
         */
        void clearConsole();

    private:
        HMS::Client &client; /**< Reference to the client */
    };
}