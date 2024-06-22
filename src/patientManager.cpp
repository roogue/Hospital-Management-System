#include <iomanip>
#include "managers/patientManager.h"
#include "cores/client.h"
#include "cores/patient.h"
#include "utils/printer.h"
#include "structs/orderedLinkedList.h"

using namespace Manager;

const int Manager::PatientManagerErrorPrefix = 100;
const std::string Manager::PatientManagerErrorMessage[] = {
    "No PM error occurred",
    "Cannot find patient with the Id",
    "Cannot find patient with the name",
    "The patient list is empty",
    "The treatment list is empty"};
const int Manager::PatientManagerErrorMessageSize = sizeof(Manager::PatientManagerErrorMessage) / sizeof(Manager::PatientManagerErrorMessage[0]);

PatientManager::PatientManager(HMS::Client &client)
    : client(client),
      patientList(),
      idIndex(0) {};

void PatientManager::managePatients()
{
    using Manager::OptionsManagePatients;
    using std::cout, std::endl;

    List::LinkedList<HMS::Patient> currentPatientList = this->patientList;
    bool managePatientsLoop = true;
    while (managePatientsLoop)
    {
        this->client.printer->printHeader();
        this->printPatientList(currentPatientList);

        cout << "1) Add Patient" << endl
             << "2) View Patient" << endl
             << "3) Search Patients" << endl
             << "4) Sort Patients" << endl
             << "5) Exit" << endl
             << "Selection: ";
        int selection;
        ErrorCode err = this->client.inputHandler.getInt(selection, 1, 5);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case OptionsManagePatients::AddPatient:
        {
            HMS::Patient newPatient(this->generatePatientId());

            this->promptPatientName(newPatient);
            this->promptPatientStatus(newPatient);

            this->patientList.addNode(newPatient);

            currentPatientList = this->patientList;

            break;
        }
        case OptionsManagePatients::ViewPatient:
        {
            int patientSize = this->getPatientSize();
            if (!patientSize)
            {
                this->client.errorHandler.addError(getErrorCode(PATIENT_LIST_EMPTY));
                continue;
            }

            this->client.printer->printHeader();
            this->printPatientList(currentPatientList);

            cout << "Choose a patient by ID: ";
            int id;
            ErrorCode err = this->client.inputHandler.getInt(id, 1, idIndex);
            if (err != this->client.inputHandler.noErrorCode())
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            HMS::Patient *patient;
            ErrorCode pmErr = this->getPatientById(patient, id);
            if (pmErr != getErrorCode(NO_PATIENT_MANAGER_ERR))
            {
                this->client.errorHandler.addError(pmErr);
                continue;
            }

            this->editPatient(*patient);

            currentPatientList = this->patientList;

            break;
        }
        case OptionsManagePatients::SearchPatient:
        {
            int patientSize = this->getPatientSize();
            if (!patientSize)
            {
                this->client.errorHandler.addError(getErrorCode(PATIENT_LIST_EMPTY));
                continue;
            }

            this->manageSearchPatient(currentPatientList);
            break;
        }
        case OptionsManagePatients::SortPatient:
        {
            this->manageSortPatient(currentPatientList);
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

void PatientManager::manageSearchPatient(LinkedList<HMS::Patient> &patientList)
{
    using Manager::OptionsManageSearchPatient;
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();
    do
    {
        this->client.printer->printHeader();
        this->printPatientList();

        cout << "Search patients by " << endl
             << "1) Name" << endl
             << "2) Status" << endl
             << "3) Treatment Type" << endl
             << "Selection: ";
        int selection;
        err = this->client.inputHandler.getInt(selection, 1, 3);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        patientList.reset();
        this->client.printer->printHeader();
        this->printPatientList();

        switch (selection)
        {
        case OptionsManageSearchPatient::SearchByName:
        {
            cout << "Patient name to search: ";
            std::string name;
            err = this->client.inputHandler.getString(name);
            if (err != this->client.inputHandler.noErrorCode())
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            // No error handling at search patient function
            // because we've checked patientList length earlier
            this->patientList.searchNodes(patientList, HMS::Patient::searchName, name);
            break;
        }
        case OptionsManageSearchPatient::SearchByStatus:
        {
            cout << "Patient status to search: " << endl;
            for (int i = 0; i < HMS::PatientStatusSize; i++)
            {
                cout << i + 1 << ") " << HMS::PatientStatusLookUp[i] << endl;
            }
            cout << "Selection: ";
            int selection;
            err = this->client.inputHandler.getInt(selection, 1, HMS::PatientStatusSize);
            if (err != this->client.inputHandler.noErrorCode())
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            this->patientList.searchNodes(patientList, HMS::Patient::searchStatus, HMS::PatientStatus(selection - 1));
            break;
        }
        case OptionsManageSearchPatient::SearchByTreatmentType:
        {
            cout << "Patient treatment type to search: " << endl;
            for (int i = 0; i < HMS::TreatmentTypeSize; i++)
            {
                cout << i + 1 << ") " << HMS::TreatmentTypeLookUp[i] << endl;
            }
            cout << "Selection: ";
            int selection;
            err = this->client.inputHandler.getInt(selection, 1, HMS::TreatmentTypeSize);
            if (err != this->client.inputHandler.noErrorCode())
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            HMS::TreatmentType treatmentType = HMS::TreatmentType(selection - 1);
            std::string formattedTreatmentType = "";
            if (treatmentType == HMS::TreatmentType::Other)
            {
                cout << "Other treatment type: ";
                err = this->client.inputHandler.getString(formattedTreatmentType);
                if (err != this->client.inputHandler.noErrorCode())
                {
                    this->client.errorHandler.addError(err);
                    continue;
                }
            }
            else
            {
                formattedTreatmentType = HMS::TreatmentTypeLookUp[treatmentType];
            }

            this->patientList.searchNodes(patientList, HMS::Patient::searchTreatmentType, formattedTreatmentType);
            break;
        }
        }

    } while (err);
}

void PatientManager::manageSortPatient(LinkedList<HMS::Patient> &patientList)
{
    using Manager::OptionManageSortPatient;
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();
    do
    {
        this->client.printer->printHeader();
        this->printPatientList(patientList);

        cout << "Sort patients by " << endl
             << "1) Appointment Dates" << endl
             << "2) Length of Stay" << endl
             << "3) Priority" << endl
             << "Selection: ";
        int selection;
        err = this->client.inputHandler.getInt(selection, 1, 3);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        this->client.printer->printHeader();
        this->printPatientList();

        switch (selection)
        {
        case OptionManageSortPatient::SortByAppointment:
        {
            patientList.sortNodes(HMS::Patient::compareTreatmentAppointment);
            break;
        }
        case OptionManageSortPatient::SortByLengthOfStay:
        {
            patientList.sortNodes(HMS::Patient::compareTreatmentDayOfStay);
            break;
        }
        case OptionManageSortPatient::SortByPriority:
        {
            patientList.sortNodes(HMS::Patient::compareTreatmentPriority);
            break;
        }
        }
    } while (err);
}

void PatientManager::editPatient(HMS::Patient &patient)
{
    using Manager::OptionsEditPatient;
    using std::cout, std::endl;

    bool editPatientLoop = true;
    while (editPatientLoop)
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient);

        cout << "1) Edit Name" << endl
             << "2) Edit Status" << endl
             << "3) Edit Treatment" << endl
             << "4) Delete Patient" << endl
             << "5) Exit from Edit Patient" << endl
             << "Selection: ";
        int selection;
        ErrorCode err = this->client.inputHandler.getInt(selection, 1, 5);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case OptionsEditPatient::EditName:
        {
            this->promptPatientName(patient);
            break;
        }
        case OptionsEditPatient::EditStatus:
        {
            this->promptPatientStatus(patient);
            break;
        }
        case OptionsEditPatient::EditTreatment:
        {
            this->manageTreatments(patient);
            break;
        }
        case OptionsEditPatient::DeletePatient:
        {
            this->patientList.deleteNode(patient);
        }
        case OptionsEditPatient::ExitEditPatient:
        {
            editPatientLoop = false;
            break;
        }
        }
    }
}

void PatientManager::manageTreatments(HMS::Patient &patient)
{
    using Manager::OptionsManageTreatment;
    using std::cout, std::endl;

    bool manageTreatmentLoop = true;
    while (manageTreatmentLoop)
    {
        this->client.printer->printHeader();
        this->printTreatmentList(patient);

        cout << "1) Add Treatment" << endl
             << "2) View Treatment" << endl
             << "3) Exit from Manage Treatment" << endl
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
        case OptionsManageTreatment::AddTreatment:
        {
            this->promptPatientTreatment(patient);
            break;
        }
        case OptionsManageTreatment::ViewTreatment:
        {
            int treatmentSize = patient.getTreatmentsSize();
            if (!treatmentSize)
            {
                this->client.errorHandler.addError(TREATMENT_LIST_EMPTY);
                continue;
            }

            this->client.printer->printHeader();
            this->printTreatmentList(patient);

            cout << "Choose treatment by index: ";
            int id;
            ErrorCode err = this->client.inputHandler.getInt(id, 1, treatmentSize);
            if (err != this->client.inputHandler.noErrorCode())
            {
                this->client.errorHandler.addError(err);
                continue;
            }

            HMS::Treatment *treatment = patient.getTreatment(id - 1);
            this->editTreatment(*treatment, patient);
            break;
        }
        case OptionsManageTreatment::ExitManageTreatment:
        {
            manageTreatmentLoop = false;
            break;
        }
        }
    }
}
void PatientManager::editTreatment(HMS::Treatment &treatment, HMS::Patient &patient)
{
    using Manager::OptionsEditTreatment;
    using std::cout, std::endl;

    bool editTreatmentLoop = true;
    while (editTreatmentLoop)
    {
        this->client.printer->printHeader();
        this->printTreatmentDetails(treatment);

        cout << "1) Edit Treatment Type" << endl
             << "2) Edit Appointment Date" << endl
             << "3) Edit Length of Stay" << endl
             << "4) Edit Priority" << endl
             << "5) Delete Treatment" << endl
             << "6) Exit from Edit Treatment" << endl
             << "Selection: ";
        int selection;
        ErrorCode err = this->client.inputHandler.getInt(selection, 1, 6);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case OptionsEditTreatment::EditTreatmentType:
        {
            this->promptTreatmentType(treatment);
            break;
        }
        case OptionsEditTreatment::EditAppointment:
        {
            this->promptTreatmentAppointment(treatment);
            break;
        }
        case OptionsEditTreatment::EditDayOfStay:
        {
            this->promptTreatmentDayOfStay(treatment);
            break;
        }
        case OptionsEditTreatment::EditPriority:
        {
            this->promptTreatmentPriority(treatment);
            break;
        }
        case OptionsEditTreatment::DeleteTreatment:
        {
            patient.deleteTreatment(treatment);
        }
        case OptionsEditTreatment::ExitEditTreatment:
        {
            editTreatmentLoop = false;
            break;
        }
        }
    }
};

void PatientManager::printPatientList()
{
    this->printPatientList(this->patientList);
};

void PatientManager::printPatientList(LinkedList<HMS::Patient> patientList)
{
    using std::cout, std::endl, std::setw, std::left;

    cout << "Patient List:" << endl;
    if (patientList.isEmpty())
    {
        cout << " - Patient list is empty - " << endl;
    }
    else
    {
        cout << setw(5) << left << "|ID"
             << setw(20) << left << "|Name"
             << setw(12) << left << "|Status"
             << setw(18) << left << "|Ongoing Treatment"
             << setw(12) << left << "|Appointment"
             << setw(15) << left << "|Length Of Stay"
             << setw(9) << left << "|Priority|"
             << endl;
        Iterator<HMS::Patient> iterator = patientList.iterate();
        while (iterator.getData() != nullptr)
        {
            HMS::Patient *patient = iterator.getData();
            HMS::Treatment *latestTreatment = patient->getLatestTreatment();
            cout << "|" << setw(4) << patient->getId() << "|"
                 << setw(19) << patient->getName().substr(0, 19) << "|"
                 << setw(11) << HMS::PatientStatusLookUp[patient->getStatus()] << "|";

            if (latestTreatment == nullptr || latestTreatment->isCompleted())
            {
                cout << setw(17) << "None" << "|"
                     << setw(11) << "" << "|"
                     << setw(14) << "" << "|"
                     << setw(8) << "" << "|"
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
};

// This function would only print the latest treatment
void PatientManager::printPatientDetails(HMS::Patient patient)
{
    using std::cout, std::endl;

    HMS::Treatment *latestTreatment = patient.getLatestTreatment();
    cout << "Patient Details: " << endl
         << "ID: " << patient.getId() << endl
         << "1) Name: " << patient.getName() << endl
         << "2) Status: " << HMS::PatientStatusLookUp[patient.getStatus()] << endl
         << "3) Latest Treatment: ";

    if (latestTreatment != nullptr)
    {
        cout << endl
             << "Treatment Type: " << latestTreatment->getFormattedTreatmentType() << endl
             << "Appointment: " << latestTreatment->getAppointment().getFormattedDate() << endl
             << "Length of stay (day): " << latestTreatment->getDayOfStay() << endl
             << "Priority: " << latestTreatment->getPriority() << endl;
    }
    else
    {
        cout << "None" << endl;
    }

    this->client.printer->printDivider();
};

// Overload so this function will print whatever treatment that is passed in
void PatientManager::printPatientDetails(HMS::Patient patient, HMS::Treatment latestTreatment)
{
    using std::cout, std::endl;

    cout << "Patient Details: " << endl
         << "ID: " << patient.getId() << endl
         << "1) Name: " << patient.getName() << endl
         << "2) Status: " << patient.getFormattedStatus() << endl
         << "3) Latest Treatment: " << endl;

    cout << "Treatment Type: " << latestTreatment.getFormattedTreatmentType() << endl
         << "Appointment: " << latestTreatment.getAppointment().getFormattedDate() << endl
         << "Length of stay (day): " << latestTreatment.getDayOfStay() << endl
         << "Priority: " << latestTreatment.getPriority() << endl;

    this->client.printer->printDivider();
};

void PatientManager::printTreatmentList(HMS::Patient patient)
{
    using std::cout, std::endl, std::setw, std::left;

    cout << "Treatment List for Patient " << patient.getName() << endl;
    if (!patient.getTreatmentsSize())
    {
        cout << " - Treatment list is empty - " << endl;
    }
    else
    {
        cout << setw(5) << left << "|Index"
             << setw(20) << left << "|Type"
             << setw(13) << left << "|Appointment"
             << setw(13) << left << "|Day Of Stay"
             << setw(10) << left << "|Priority"
             << endl;

        Iterator<HMS::Treatment> iterator = patient.getTreatmentIterator();
        int index = 0;
        while (iterator.getData() != nullptr)
        {
            HMS::Treatment *treatment = iterator.getData();
            cout << "|" << setw(5) << ++index << "|"
                 << setw(19) << treatment->getFormattedTreatmentType() << "|"
                 << setw(12) << treatment->getAppointment().getFormattedDate() << "|"
                 << setw(12) << treatment->getDayOfStay() << "|"
                 << setw(9) << treatment->getPriority()
                 << endl;
            iterator.next();
        }
    }
    this->client.printer->printDivider();
}

void PatientManager::printTreatmentDetails(HMS::Treatment treatment)
{
    using std::cout, std::endl;

    cout << "Treatment Details: " << endl
         << "1) Treatment Type: " << treatment.getFormattedTreatmentType() << endl
         << "2) Appointment: " << treatment.getAppointment().getFormattedDate() << endl
         << "3) Length of stay (day): " << treatment.getDayOfStay() << endl
         << "4) Priority: " << treatment.getPriority() << endl;

    this->client.printer->printDivider();
}

int PatientManager::getIdIndex()
{
    return this->idIndex;
};

void PatientManager::addPatient(HMS::Patient &patient)
{
    this->patientList.addNode(patient);
}

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

ErrorCode PatientManager::getPatientById(HMS::Patient *&patient, int id)
{
    Iterator<HMS::Patient> iterator = this->patientList.iterate();
    while (iterator.getData() != nullptr)
    {
        HMS::Patient *currentPatient = iterator.getData();
        if (currentPatient->getId() == id)
        {
            patient = currentPatient;
            return getErrorCode(NO_PATIENT_MANAGER_ERR);
        }
        iterator.next();
    }

    return getErrorCode(PATIENT_ID_NOT_FOUND);
}

Iterator<HMS::Patient> PatientManager::getPatientListIterator()
{
    return this->patientList.iterate();
}

int PatientManager::generatePatientId()
{
    return ++this->idIndex;
};

void PatientManager::promptPatientName(HMS::Patient &patient)
{
    using std::cout, std::endl;

    std::string name;
    ErrorCode err = this->client.inputHandler.noErrorCode();
    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient);

        cout << "Patient Name: ";
        err = this->client.inputHandler.getString(name);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
        }
    } while (err);

    patient.setName(name);
};

ErrorCode PatientManager::getErrorCode(PatientManagerError error)
{
    return (PatientManagerErrorPrefix + error);
}
ErrorCode PatientManager::noErrorCode()
{
    return PatientManagerErrorPrefix + PatientManagerError::NO_PATIENT_MANAGER_ERR;
}

void PatientManager::promptPatientStatus(HMS::Patient &patient)
{
    using std::cout, std::endl;

    HMS::PatientStatus status;
    ErrorCode err = this->client.inputHandler.noErrorCode();
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
        if (err != this->client.inputHandler.noErrorCode())
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

    Handler::Date date;
    do
    {
        this->client.printer->printHeader();
        this->printPatientDetails(patient);

        cout << HMS::PatientStatusLookUp[status]
             << " Date for Patient (" << patient.getName() << ") (DD/MM/YYYY): ";

        err = this->client.inputHandler.getDate(date);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }
    } while (err);

    if (status == HMS::PatientStatus::Admitted)
    {
        patient.addAdmissionDate(date);
    }
    else
    {
        patient.addDischargeDate(date);
        HMS::Treatment *latestTreatment = patient.getLatestTreatment();
        if (latestTreatment != nullptr)
        {
            latestTreatment->setCompleted();
        }
    }
};

void PatientManager::promptPatientTreatment(HMS::Patient &patient)
{
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();

    HMS::Treatment treatment;

    this->promptTreatmentType(treatment);
    this->promptTreatmentAppointment(treatment);
    this->promptTreatmentDayOfStay(treatment);
    this->promptTreatmentPriority(treatment);

    patient.addTreatment(treatment);
};

void PatientManager::promptTreatmentType(HMS::Treatment &treatment)
{
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();

    int treatmentTypeSelection;
    do
    {
        this->client.printer->printHeader();
        this->printTreatmentDetails(treatment);

        cout << "Patient treatment: " << endl;
        for (int i = 0; i < HMS::TreatmentTypeSize; i++)
        {
            cout << i + 1 << ") " << HMS::TreatmentTypeLookUp[i] << endl;
        }
        cout << "Selection: ";
        err = this->client.inputHandler.getInt(treatmentTypeSelection, 1, HMS::TreatmentTypeSize);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }
    } while (err);
    treatment.setTreatmentType(HMS::TreatmentType(treatmentTypeSelection - 1));

    std::string otherType = "";
    do
    {
        this->client.printer->printHeader();
        this->printTreatmentDetails(treatment);

        if (treatment.getTreatmentType() != HMS::TreatmentType::Other)
        {
            break;
        }

        cout << "Specify other treatment type: ";
        err = this->client.inputHandler.getString(otherType);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }
    } while (err);
    treatment.setOtherTreatmentType(otherType);
}

void PatientManager::promptTreatmentAppointment(HMS::Treatment &treatment)
{
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();

    Handler::Date appointment;
    do
    {
        this->client.printer->printHeader();
        this->printTreatmentDetails(treatment);

        cout << "Treatment appointment date (DD/MM/YYYY): ";
        err = this->client.inputHandler.getDate(appointment);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }
    } while (err);

    treatment.setAppointment(appointment);
}

void PatientManager::promptTreatmentDayOfStay(HMS::Treatment &treatment)
{
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();

    int dayOfStay;
    do
    {
        this->client.printer->printHeader();
        this->printTreatmentDetails(treatment);

        cout << "Patient length of stay (day): ";
        err = this->client.inputHandler.getInt(dayOfStay);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

    } while (err);
    treatment.setDayOfStay(dayOfStay);
};

void PatientManager::promptTreatmentPriority(HMS::Treatment &treatment)
{
    using std::cout, std::endl;

    ErrorCode err = this->client.inputHandler.noErrorCode();

    int priority;
    do
    {
        this->client.printer->printHeader();
        this->printTreatmentDetails(treatment);

        cout << "Patient priority: ";
        err = this->client.inputHandler.getInt(priority);
        if (err != this->client.inputHandler.noErrorCode())
        {
            this->client.errorHandler.addError(err);
            continue;
        }

    } while (err);
    treatment.setPriority(priority);
};
