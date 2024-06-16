#include <iomanip>
#include "managers/reportManager.h"
#include "cores/client.h"
#include "utils/printer.h"

using namespace Manager;

bool Event::operator<(Event &other)
{
    return this->date < other.date;
};

const int Manager::ReportManagerErrorPrefix = 300;
const std::string Manager::ReportManagerErrorMessage[] = {
    "No RM error occurred",
    "Patient list is empty"};
const int Manager::ReportManagerErrorMessageSize = sizeof(Manager::ReportManagerErrorMessage) / sizeof(Manager::ReportManagerErrorMessage[0]);

ReportManager::ReportManager(HMS::Client &client) : client(client){};

void ReportManager::manageReport()
{
    using Manager::OptionsManageReport;
    using std::cout, std::endl, std::setw, std::left;

    bool manageReportLoop = true;
    while (manageReportLoop)
    {
        this->client.printer->printHeader();

        cout << "1) Generate Overall Summary Report" << endl
             << "2) Generate Report For Patient" << endl
             << "3) Exit Manage Report" << endl
             << "Selection: ";
        int selection;
        ErrorCode err = this->client.inputHandler.getInt(selection, 1, 3);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case OptionsManageReport::GenerateOverallReport:
        {
            this->client.printer->printHeader();

            int patientSize = this->client.patientManager->getPatientSize();
            cout << "Total Patient: " << patientSize << endl;
            this->client.printer->printDivider();

            Iterator<HMS::Patient> iterator = this->client.patientManager->getPatientListIterator();

            LinkedList<HMS::Patient> admittedPatients;
            LinkedList<HMS::Patient> dischargedPatients;

            while (iterator.getData() != nullptr)
            {
                HMS::Patient *patient = iterator.getData();
                if (patient->getStatus() == HMS::PatientStatus::Admitted)
                {
                    admittedPatients.addNode(*patient);
                }
                else
                {
                    dischargedPatients.addNode(*patient);
                }

                iterator.next();
            }

            cout << "Admitted Patient: (" << admittedPatients.getSize() << ")" << endl;
            if (admittedPatients.isEmpty())
            {
                cout << " - Patient list is empty - " << endl;
            }
            else
            {
                cout << setw(5) << left << "|ID"
                     << setw(20) << left << "|Name" << "|"
                     << endl;
                iterator = admittedPatients.iterate();
                while (iterator.getData() != nullptr)
                {
                    HMS::Patient *patient = iterator.getData();
                    cout << "|" << setw(4) << patient->getId() << "|"
                         << setw(19) << patient->getName().substr(0, 19) << "|"
                         << endl;
                    iterator.next();
                }
            }

            this->client.printer->printDivider();

            cout << "Discharged Patient: (" << dischargedPatients.getSize() << ")" << endl;
            if (dischargedPatients.isEmpty())
            {
                cout << " - Patient list is empty - " << endl;
            }
            else
            {
                cout << setw(5) << left << "|ID"
                     << setw(20) << left << "|Name" << "|"
                     << endl;
                iterator = dischargedPatients.iterate();
                while (iterator.getData() != nullptr)
                {
                    HMS::Patient *patient = iterator.getData();
                    cout << "|" << setw(4) << patient->getId() << "|"
                         << setw(19) << patient->getName().substr(0, 19) << "|"
                         << endl;
                    iterator.next();
                }
            }

            this->client.printer->printDivider();
            cout << "Press 'Enter' to continue..." << endl;
            this->client.printer->printDivider();
            this->client.inputHandler.pause();

            break;
        }
        case OptionsManageReport::GenerateReportForPatient:
        {
            if (this->client.patientManager->getPatientSize() == 0)
            {
                this->client.errorHandler.addError(this->getErrorCode(ReportManagerError::RM_PATIENT_LIST_EMPTY));
                break;
            }

            using std::cout, std::endl;

            ErrorCode err = this->client.inputHandler.noErrorCode();
            HMS::Patient *patient;
            while (true)
            {
                this->client.printer->printHeader();
                this->client.patientManager->printPatientList();

                cout << "Choose patient by ID: ";
                int id;
                ErrorCode err = this->client.inputHandler.getInt(id, 1, this->client.patientManager->getIdIndex());
                if (err != this->client.inputHandler.noErrorCode())
                {
                    this->client.errorHandler.addError(err);
                    continue;
                }

                ErrorCode pmErr = this->client.patientManager->getPatientById(patient, id);
                if (pmErr != this->client.patientManager->noErrorCode())
                {
                    this->client.errorHandler.addError(pmErr);
                    continue;
                }

                break;
            }

            this->client.printer->printHeader();
            cout << "Patient Report: " << endl
                 << "ID: " << patient->getId() << endl
                 << "Name: " << patient->getName() << endl
                 << "Status: " << HMS::PatientStatusLookUp[patient->getStatus()] << endl
                 << "Treatment Timelines: " << endl;

            LinkedList<Event> events;

            Iterator<HMS::Treatment> treatmentsIterator = patient->getTreatmentIterator();
            while (treatmentsIterator.getData() != nullptr)
            {
                HMS::Treatment *treatment = treatmentsIterator.getData();
                Event newEvent = {treatment->getAppointment(), "Treatment: " + treatment->getFormattedTreatmentType()};
                events.addNode(newEvent);
                treatmentsIterator.next();
            }

            Iterator<Handler::Date> admissionsIterator = patient->getAdmissionsIterator();
            while (admissionsIterator.getData() != nullptr)
            {
                Handler::Date *admission = admissionsIterator.getData();
                Event newEvent = {*admission, "Admitted"};
                events.addNode(newEvent);
                admissionsIterator.next();
            }
            Iterator<Handler::Date> dischargesIterator = patient->getDischargesIterator();
            while (dischargesIterator.getData() != nullptr)
            {
                Handler::Date *discharge = dischargesIterator.getData();
                Event newEvent = {*discharge, "Discharged"};
                events.addNode(newEvent);
                dischargesIterator.next();
            }

            events.sortNodes();

            Iterator<Event> eventIterator = events.iterate();
            while (eventIterator.getData() != nullptr)
            {
                Event *event = eventIterator.getData();
                cout << endl
                     << "(" << event->date.getFormattedDate() << ") " << eventIterator.getData()->description << endl;
                eventIterator.next();
            }

            this->client.printer->printDivider();
            cout << "Press 'Enter' to continue..." << endl;
            this->client.printer->printDivider();
            this->client.inputHandler.pause();
            break;
        }
        case OptionsManageReport::ExitManageReport:
        {
            manageReportLoop = false;
            break;
        }
        }
    }
}

ErrorCode ReportManager::getErrorCode(ReportManagerError error)
{
    return (ReportManagerErrorPrefix + error);
}
ErrorCode ReportManager::noErrorCode()
{
    return ReportManagerErrorPrefix + ReportManagerError::NO_REPORT_MANAGER_ERR;
}
