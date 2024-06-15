#pragma once

#include "handlers/errorHandler.h"
#include "handlers/inputHandler.h"
#include "managers/patientManager.h"
#include "managers/transactionManager.h"
#include "cores/patient.h"

// Forward declaration
namespace Manager
{
    class PatientManager;
    class TransactionManager;
    class ReportManager;
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
        Manager::TransactionManager *transactionManager;
        Manager::ReportManager *reportManager;
        Util::Printer *printer;
    };
}