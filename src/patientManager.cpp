#include <iomanip>
#include "managers/patientManager.h"
#include "cores/client.h"
#include "cores/patient.h"
#include "utils/printer.h"
#include "structs/orderedLinkedList.h"

using namespace Manager;

const int Manager::PatientManagerErrorPrefix = 100;

const std::string Manager::PatientManagerErrorMessage[] = {
    "No error occurred",
    "Cannot find patient with the Id",
    "The patient list is empty"};
const int Manager::PatientManagerErrorMessageSize = sizeof(Manager::PatientManagerErrorMessage) / sizeof(Manager::PatientManagerErrorMessage[0]);
;

PatientManager::PatientManager(HMS::Client &client)
    : client(client),
      patientList(),
      idIndex(0){};

void PatientManager::managePatients()
{
    using Handler::InputError;
    using std::cout, std::endl;
    using namespace HMS;

    bool managePatientsLoop = true;
    while (managePatientsLoop)
    {
        this->client.printer->printHeader();
        this->printPatientList();

        cout << "1) Add Patient" << endl
             << "2) View Patient" << endl
             << "3) Exit" << endl
             << "Selection: ";
        int selection;
        InputError err = this->client.inputHandler.getInt(selection, 1, 3);
        if (err)
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case OptionsManagePatients::AddPatient:
        {
            Patient newPatient(this->generatePatientId());

            this->promptName(newPatient);
            this->promptStatus(newPatient);

            if (newPatient.getStatus() == PatientStatus::Admitted)
            {
                this->promptTreatment(newPatient);
            }

            this->patientList.addNode(newPatient);

            break;
        }
        case OptionsManagePatients::ViewPatient:
        {
            int patientSize = this->getPatientSize();
            if (!patientSize)
            {
                this->client.errorHandler.addError(PATIENT_LIST_EMPTY);
                continue;
            }

            this->client.printer->printHeader();
            this->printPatientList();

            cout << "Choose a patient by ID: ";
            int id;
            InputError err = this->client.inputHandler.getInt(id, 1, patientSize);
            if (err)
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            Patient *patient;
            PatientManagerError pmErr = this->searchPatientById(patient, id);
            if (pmErr)
            {
                this->client.errorHandler.addError(pmErr);
                continue;
            }

            this->printPatientDetails(*patient);

            break;
        }
        case OptionsManagePatients::ExitManagePatients:
        {
            managePatientsLoop = false;
            break;
        }
        }
    }
};

int PatientManager::generatePatientId()
{
    return ++this->idIndex;
};
void PatientManager::printPatientList()
{
    using std::cout, std::endl, std::setw, std::left;

    cout << "Patient List:" << endl;
    int patientSize = this->patientList.getSize();
    if (!patientSize)
    {
        cout << " - Patient list is empty - " << endl;
    }
    else
    {
        cout << setw(5) << left << "|ID"
             << setw(20) << left << "|Name"
             << setw(12) << left << "|Status"
             << setw(18) << left << "|Ongoing Treatment"
             << endl;
        for (int i = 0; i < patientSize; i++)
        {
            HMS::Patient *patient = this->getPatient(i);
            patient->getLatestTreatment()->getTreatmentType();
            cout << "|" << setw(4) << patient->getId() << "|"
                 << setw(19) << patient->getName().substr(0, 19) << "|"
                 << setw(11) << HMS::PatientStatusLookUp[patient->getStatus()] << "|"
                  << setw(17) << (patient->getStatus() == HMS::PatientStatus::Admitted ? patient->getLatestTreatment()->getFormattedTreatmentType() : "None")
                 << endl;
        }
    }
    this->client.printer->printDivider();
};
void PatientManager::printPatientDetails(HMS::Patient patient)
{
    using std::cout, std::endl;

    cout << "Patient Details: " << endl
         << "ID: " << patient.getId() << endl
         << "1) Name: " << patient.getName() << endl
         << "2) Status: " << HMS::PatientStatusLookUp[patient.getStatus()] << endl
         << "3) Latest Treatment: " << endl;

    this->client.printer->printDivider();
};
void PatientManager::printPatientDetails(HMS::Patient patient, HMS::Treatment latestTreatment)
{
    using std::cout, std::endl;

    cout << "Patient Details: " << endl
         << "ID: " << patient.getId() << endl
         << "1) Name: " << patient.getName() << endl
         << "2) Status: " << HMS::PatientStatusLookUp[patient.getStatus()] << endl
         << "3) Latest Treatment: " << endl;

    cout << "Treatment Type: " << latestTreatment.getFormattedTreatmentType() << endl
         << "Appointment: " << latestTreatment.getAppointment().getFormattedDate() << endl
         << "Length of stay (day): " << latestTreatment.getDayOfStay() << endl
         << "Priority: " << latestTreatment.getPriority() << endl;

    this->client.printer->printDivider();
};

int PatientManager::getPatientSize()
{
    return this->patientList.getSize();
}

HMS::Patient *PatientManager::getPatient(int index)
{
    return this->patientList.getData(index);
};
HMS::Patient *PatientManager::getPatient(HMS::Patient patient)
{
    return this->patientList.getData(patient);
};

PatientManagerError PatientManager::searchPatientById(HMS::Patient *&patient, int id)
{
    for (int i = 0; i < this->getPatientSize(); i++)
    {
        HMS::Patient *currentPatient = this->getPatient(i);
        if (currentPatient->getId() == id)
        {
            patient = currentPatient;
            return NO_PATIENT_MANAGER_ERR;
        }
    }

    return PATIENT_ID_NOT_FOUND;
}

void PatientManager::promptName(HMS::Patient &patient)
{
    using std::cout, std::endl;

    std::string name;
    Handler::InputError err = Handler::InputError::NO_INPUT_ERR;
    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient);

        cout << "Patient Name: ";
        err = this->client.inputHandler.getString(name);
        if (err)
        {
            this->client.errorHandler.addError(err);
        }
    } while (err);

    patient.setName(name);
};

void PatientManager::promptStatus(HMS::Patient &patient)
{
    using std::cout, std::endl;

    HMS::PatientStatus status;
    Handler::InputError err = Handler::InputError::NO_INPUT_ERR;
    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient);

        cout << "Patient status:" << endl;
        for (int i = 0; i < HMS::PatientStatusSize; i++)
        {
            cout << i + 1 << ") " << HMS::PatientStatusLookUp[i] << endl;
        }
        cout << "Selection: ";
        int selection;
        err = this->client.inputHandler.getInt(selection, 1, HMS::PatientStatusSize);
        if (err)
        {
            this->client.errorHandler.addError(err);
            continue;
        }
        else
        {
            status = HMS::PatientStatus(selection - 1);
        }
    } while (err);

    patient.setStatus(status);
};
void PatientManager::promptTreatment(HMS::Patient &patient)
{
    using std::cout, std::endl;

    HMS::Treatment treatment;
    Handler::InputError err = Handler::InputError::NO_INPUT_ERR;
    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient, treatment);

        cout << "Patient treatment: " << endl;
        for (int i = 0; i < HMS::TreatmentTypeSize; i++)
        {
            cout << i + 1 << ") " << HMS::TreatmentTypeLookUp[i] << endl;
        }
        cout << "Selection: ";
        int selection;
        err = this->client.inputHandler.getInt(selection, 1, HMS::TreatmentTypeSize);
        if (err)
        {
            this->client.errorHandler.addError(err);
            continue;
        }
        else
        {
            treatment.setTreatmentType(HMS::TreatmentType(selection - 1));
        }

        if (treatment.getTreatmentType() == HMS::TreatmentType::Other)
        {
            std::string otherType;
            cout << "Specify other treatment type: ";
            err = this->client.inputHandler.getString(otherType);
            if (err)
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            treatment.setOtherTreatmentType(otherType);
        }

    } while (err);

    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient, treatment);

        Handler::Date appointment;
        cout << "Treatment appointment date (DD/MM/YYYY): ";
        err = this->client.inputHandler.getDate(appointment);
        if (err)
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        treatment.setAppointment(appointment);
    } while (err);

    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient, treatment);

        int dayOfStay;
        cout << "Patient length of stay (day): ";
        err = this->client.inputHandler.getInt(dayOfStay);
        if (err)
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        treatment.setDayOfStay(dayOfStay);
    } while (err);

    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient, treatment);

        int priority;
        cout << "Patient priority: ";
        err = this->client.inputHandler.getInt(priority);
        if (err)
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        treatment.setPriority(priority);
    } while (err);

    patient.addTreatment(treatment);
};