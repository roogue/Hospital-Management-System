#pragma once

#include <iostream>
#include "cores/client.h"

namespace Util
{
    class Printer
    {
    public:
        Printer(HMS::Client &client);

        void printHeader();
        void printDivider();
        void clearConsole();

    private:
        HMS::Client &client;
    };

}