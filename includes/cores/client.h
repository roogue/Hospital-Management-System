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
    /**
     * @brief Enumeration for the main menu options in the Hospital Management System.
     */
    enum OptionsMainMenu
    {
        ManagePatients = 1,   /**< Option to manage patients */
        ManageTransactions,   /**< Option to manage transactions */
        GenerateReport,       /**< Option to generate reports */
        ExitProgram           /**< Option to exit the program */
    };

    /**
     * @brief Client class for the Hospital Management System.
     * This class handles the main functionality of the HMS client, including managing patients, transactions, and reports.
     */
    class Client
    {
    public:
        /**
         * @brief Constructor for the Client class.
         * Initializes the Client object and sets up necessary managers and handlers.
         */
        Client();
        
        /**
         * @brief Destructor for the Client class.
         * Cleans up allocated resources.
         */
        ~Client();

        Handler::ErrorHandler errorHandler;             /**< Error handler for managing errors in the system */
        Handler::InputHandler inputHandler;             /**< Input handler for managing user inputs */
        Manager::PatientManager *patientManager;        /**< Pointer to the patient manager */
        Manager::TransactionManager *transactionManager;/**< Pointer to the transaction manager */
        Manager::ReportManager *reportManager;          /**< Pointer to the report manager */
        Util::Printer *printer;                         /**< Pointer to the printer utility */
    };
}
