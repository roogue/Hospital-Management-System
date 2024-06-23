#include <iostream>
#include "cores/client.h"
#include "handlers/inputHandler.h"
#include "managers/patientManager.h"
#include "managers/transactionManager.h"
#include "managers/reportManager.h"
#include "utils/printer.h"

using namespace HMS;

Client::Client()
    : errorHandler(),
      inputHandler()
{
    // Initialize and assign new instances of various managers and utilities to the client
    patientManager = new Manager::PatientManager(*this);
    transactionManager = new Manager::TransactionManager(*this);
    reportManager = new Manager::ReportManager(*this);
    printer = new Util::Printer(*this);

    // Register error messages with errorHandler function for different components
    errorHandler.registerErrorMessage(Handler::InputErrorPrefix, Handler::InputErrorMessage, Handler::InputErrorMessageSize);
    errorHandler.registerErrorMessage(Manager::PatientManagerErrorPrefix, Manager::PatientManagerErrorMessage, Manager::PatientManagerErrorMessageSize);
    errorHandler.registerErrorMessage(Manager::TransactionManagerErrorPrefix, Manager::TransactionManagerErrorMessage, Manager::TransactionManagerErrorMessageSize);
    errorHandler.registerErrorMessage(Manager::ReportManagerErrorPrefix, Manager::ReportManagerErrorMessage, Manager::ReportManagerErrorMessageSize);
}

Client::~Client()
{
    // Clean up dynamically allocated resources
    delete patientManager;
    delete printer;
}
