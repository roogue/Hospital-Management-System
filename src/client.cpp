#include <iostream>
#include "cores/client.h"
#include "handlers/inputHandler.h"
#include "managers/patientManager.h"
#include "utils/printer.h"

using namespace HMS;

Client::Client()
    : errorHandler(),
      inputHandler()
{
    patientManager = new Manager::PatientManager(*this);
    printer = new Util::Printer(*this);

    errorHandler.registerErrorMessage(Handler::InputErrorPrefix, Handler::InputErrorMessage, Handler::InputErrorMessageSize);
    errorHandler.registerErrorMessage(Manager::PatientManagerErrorPrefix, Manager::PatientManagerErrorMessage, Manager::PatientManagerErrorMessageSize);
}

Client::~Client()
{
    delete patientManager;
    delete printer;
}
