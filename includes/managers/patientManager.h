#pragma once

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

    extern const int PatientManagerErrorPrefix;

    enum PatientManagerError
    {
        NO_PATIENT_MANAGER_ERR,
        PATIENT_ID_NOT_FOUND,
        PATIENT_LIST_EMPTY
    };
    extern const std::string PatientManagerErrorMessage[];
    extern const int PatientManagerErrorMessageSize;

    class PatientManager
    {
    public:
        PatientManager(HMS::Client &client);
        void managePatients();

        int generatePatientId();
        void printPatientList();
        void printPatientDetails(HMS::Patient patient);
        void printPatientDetails(HMS::Patient patient, HMS::Treatment latestTreatment);

        int getPatientSize();
        HMS::Patient *getPatient(int index);
        HMS::Patient *getPatient(HMS::Patient patient);
        PatientManagerError searchPatientById(HMS::Patient *&patient, int id);

    private:
        HMS::Client &client;
        LinkedList<HMS::Patient> patientList;
        int idIndex;

        void promptName(HMS::Patient &patient);
        void promptStatus(HMS::Patient &patient);
        void promptTreatment(HMS::Patient &patient);
    };
};