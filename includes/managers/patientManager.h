#pragma once

#include "handlers/errorHandler.h"
#include "structs/linkedList.h"
#include "cores/patient.h"
#include "cores/client.h"

// Forward declaration
namespace HMS
{
    class Client;
}

namespace Manager
{
    enum OptionsManagePatients
    {
        AddPatient = 1,
        ViewPatient,
        ExitManagePatients
    };
    enum OptionsEditPatient
    {
        EditName = 1,
        EditStatus,
        EditTreatment,
        DeletePatient,
        ExitEditPatient,
    };
    enum OptionsManageTreatment
    {
        AddTreatment = 1,
        ViewTreatment,
        ExitManageTreatment,
    };
    enum OptionsEditTreatment
    {
        EditTreatmentType = 1,
        EditAppointment,
        EditDayOfStay,
        EditPriority,
        DeleteTreatment,
        ExitEditTreatment,
    };

    extern const int PatientManagerErrorPrefix;
    enum PatientManagerError
    {
        NO_PATIENT_MANAGER_ERR,
        PATIENT_ID_NOT_FOUND,
        PATIENT_LIST_EMPTY,
        TREATMENT_LIST_EMPTY
    };
    extern const std::string PatientManagerErrorMessage[];
    extern const int PatientManagerErrorMessageSize;

    class PatientManager
    {
    public:
        PatientManager(HMS::Client &client);
        void managePatients();
        void editPatient(HMS::Patient &patient);
        void manageTreatments(HMS::Patient &patient);
        void editTreatment(HMS::Treatment &treatment, HMS::Patient &patient);

        void printPatientList();
        void printPatientDetails(HMS::Patient patient);
        void printPatientDetails(HMS::Patient patient, HMS::Treatment latestTreatment);
        void printTreatmentList(HMS::Patient patient);
        void printTreatmentDetails(HMS::Treatment treatment);

        int getPatientSize();
        HMS::Patient *getPatient(int index);
        HMS::Patient *getPatient(HMS::Patient patient);
        ErrorCode searchPatientById(HMS::Patient *&patient, int id);

    private:
        HMS::Client &client;
        LinkedList<HMS::Patient> patientList;
        int idIndex;

        int generatePatientId();

        void promptPatientName(HMS::Patient &patient);
        void promptPatientStatus(HMS::Patient &patient);
        void promptPatientTreatment(HMS::Patient &patient);

        void promptTreatmentType(HMS::Treatment &treatment);
        void promptTreatmentAppointment(HMS::Treatment &treatment);
        void promptTreatmentDayOfStay(HMS::Treatment &treatment);
        void promptTreatmentPriority(HMS::Treatment &treatment);

        ErrorCode getErrorCode(PatientManagerError error);
    };
};