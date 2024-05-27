#pragma once

#include "handlers/errorHandler.h"
#include "handlers/inputHandler.h"
#include "managers/patientManager.h"
#include "cores/patient.h"

// Forward declaration
namespace Manager
{
    class PatientManager;
}
namespace Util
{
    class Printer;
}

namespace HMS
{
    enum OptionsMainMenu
    {
        ManagePatients = 1,
        ManageTransactions,
        GenerateReport,
        ExitProgram
    };

    class Client
    {
    public:
        Client();
        ~Client();

        Handler::ErrorHandler errorHandler;
        Handler::InputHandler inputHandler;
        Manager::PatientManager *patientManager;
        Util::Printer *printer;
    };
}