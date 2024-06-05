#include <iostream>
#include "handlers/errorHandler.h"
#include "handlers/inputHandler.h"
#include "cores/client.h"
#include "managers/patientManager.h"
#include "utils/printer.h"
#include "cores/patient.h"

int main()
{    
    HMS::Client client;

    using Handler::InputError;
    using std::cout, std::endl;

    while (true)
    {
        client.printer->printHeader();

        cout << "1) Manage Patients" << endl
             << "2) Manage Transaction" << endl
             << "3) Generate Reports" << endl
             << "4) Exit" << endl;
        cout << "Selection: ";
        int selection;
        ErrorCode err = client.inputHandler.getInt(selection, 1, 4);
        if (err)
        {
            client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case HMS::OptionsMainMenu::ManagePatients:
        {
            client.patientManager->managePatients();
            break;
        }
        case HMS::OptionsMainMenu::ManageTransactions:
        {
            break;
        }
        case HMS::OptionsMainMenu::GenerateReport:
        {
            break;
        }
        case HMS::OptionsMainMenu::ExitProgram:
        {
            exit(0);
            break;
        }
        }
    }
}