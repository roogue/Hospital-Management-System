#include <iostream>
#include <iomanip>
#include "managers/transactionManager.h"
#include "cores/client.h"
#include "utils/printer.h"

using namespace Manager;

// Static constants for error handling in TransactionManager
const int Manager::TransactionManagerErrorPrefix = 200;
const std::string Manager::TransactionManagerErrorMessage[] = {
    "No TM error occurred",
    "No admitted patient found",
};
const int Manager::TransactionManagerErrorMessageSize = sizeof(Manager::TransactionManagerErrorMessage) / sizeof(Manager::TransactionManagerErrorMessage[0]);

TransactionManager::TransactionManager(HMS::Client &client)
    : client(client) {};

void TransactionManager::manageTransaction()
{
    using Manager::OptionsManageTransaction;
    using std::cout, std::endl;

    // Reset transaction list at the start of management
    this->resetTransactionList();

    bool manageTransactionLoop = true;
    while (manageTransactionLoop)
    {
        this->client.printer->printHeader();
        this->printTransactionList();

        // Display menu options
        cout << "1) Discharge Patient" << endl
             << "2) Sort Transaction" << endl
             << "3) Exit Manage Transaction" << endl
             << "Selection: ";
        // Get user selection
        int selection;
        ErrorCode err = this->client.inputHandler.getInt(selection, 1, 3);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        // Process user selection
        switch (selection)
        {
        case OptionsManageTransaction::DischargePatient:
        {
            // Check if there are admitted patients to discharge
            if (this->client.patientManager->getPatientSize() == 0)
            {
                this->client.errorHandler.addError(getErrorCode(NO_ADMITTED_PATIENT));
                continue;
            }

            // Get patient to discharge from the transaction list
            Iterator<HMS::Patient> iterator = this->transactionList.iterate();
            HMS::Patient *patient = this->client.patientManager->getPatient(*(iterator.getData()));

            this->client.printer->printHeader();

            // Prompt for discharge date and update patient status,
            // and set the treatment as completed.
            cout << "Discharge Date for Patient (" << patient->getName() << ") (DD/MM/YYYY): ";
            Handler::Date date;
            err = this->client.inputHandler.getDate(date);
            if (err != this->client.inputHandler.noErrorCode())
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            patient->addDischargeDate(date);
            HMS::Treatment *latestTreatment = patient->getLatestTreatment();
            if (latestTreatment != nullptr)
            {
                latestTreatment->setCompleted();
            }
            patient->setStatus(HMS::PatientStatus::Discharged);

            // Remove patient from transaction list
            this->transactionList.dequeue();
            break;
        }
        case OptionsManageTransaction::SortTransaction:
        {
            // Manage sorting options for the transaction list
            this->manageSortTransaction();
            break;
        }
        case OptionsManageTransaction::ExitManageTransaction:
        {
            // Exit the manage transaction loop
            manageTransactionLoop = false;
            break;
        }
        }
    }
}

void TransactionManager::manageSortTransaction()
{
    using Manager::OptionsSortTransaction;
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();
    do
    {
        this->client.printer->printHeader();
        this->printTransactionList();

        // Display sorting options
        cout << "Sort patients by " << endl
             << "1) Appointment Dates" << endl
             << "2) Length of Stay" << endl
             << "3) Priority" << endl
             << "Selection: ";
        int selection;
        // Get user selection for sorting criteria
        err = this->client.inputHandler.getInt(selection, 1, 4);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        this->client.printer->printHeader();
        this->printTransactionList();

        // Sort transaction list based on user selection
        switch (selection)
        {
        case OptionsSortTransaction::SortTransactionByAppointment:
        {
            this->transactionList.sortQueue(HMS::Patient::compareTreatmentAppointment);
            break;
        }
        case OptionsSortTransaction::SortTransactionByLengthOfStay:
        {
            this->transactionList.sortQueue(HMS::Patient::compareTreatmentDayOfStay);
            break;
        }
        case OptionsSortTransaction::SortTransactionByPriority:
        {
            this->transactionList.sortQueue(HMS::Patient::compareTreatmentPriority);
            break;
        }
        }
    } while (err);
}

void TransactionManager::printTransactionList()
{
    using std::cout, std::endl, std::setw, std::left;

    cout << "Transaction List:" << endl;
    if (this->transactionList.isEmpty())
    {
        cout << " - Transaction list is empty - " << endl;
    }
    else
    {
        // Print formatted transaction list
        cout << setw(5) << left << "|ID"
             << setw(20) << left << "|Name"
             << setw(12) << left << "|Status"
             << setw(18) << left << "|Ongoing Treatment"
             << setw(12) << left << "|Appointment"
             << setw(15) << left << "|Length Of Stay"
             << setw(9) << left << "|Priority|"
             << endl;
        Iterator<HMS::Patient> iterator = this->transactionList.iterate();
        while (iterator.getData() != nullptr)
        {
            HMS::Patient *patient = iterator.getData();
            HMS::Treatment *latestTreatment = patient->getLatestTreatment();
            cout << "|" << setw(4) << patient->getId() << "|"
                 << setw(19) << patient->getName().substr(0, 19) << "|"
                 << setw(11) << HMS::PatientStatusLookUp[patient->getStatus()] << "|";

            // Print None, if the patient had completed his treatment
            if (latestTreatment == nullptr || latestTreatment->isCompleted())
            {
                cout << setw(17) << "None"
                     << setw(11) << "|"
                     << setw(14) << "|"
                     << setw(8) << "|"
                     << endl;
            }
            else
            {
                cout << setw(17) << latestTreatment->getFormattedTreatmentType() << "|"
                     << setw(11) << latestTreatment->getAppointment().getFormattedDate() << "|"
                     << setw(14) << latestTreatment->getDayOfStay() << "|"
                     << setw(8) << latestTreatment->getPriority() << "|"
                     << endl;
            }

            iterator.next();
        }
    }
    this->client.printer->printDivider();
}

ErrorCode TransactionManager::getErrorCode(TransactionManagerError error)
{
    return (Manager::TransactionManagerErrorPrefix + error);
};
ErrorCode TransactionManager::noErrorCode()
{
    return (Manager::TransactionManagerErrorPrefix + Manager::TransactionManagerError::NO_TRANSACTION_MANAGER_ERR);
}

void TransactionManager::resetTransactionList()
{
    this->transactionList.resetQueue();

    // Iterate through patient list and enqueue admitted patients
    Iterator<HMS::Patient> iterator = this->client.patientManager->getPatientListIterator();
    while (iterator.getData() != nullptr)
    {
        HMS::Patient *patient = iterator.getData();
        if (patient->getStatus() == HMS::PatientStatus::Admitted)
        {
            this->transactionList.enqueue(*(iterator.getData()));
        }

        iterator.next();
    }
}