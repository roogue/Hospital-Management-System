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
    /**
     * @brief Enumeration for options to manage patients.
     */
    enum OptionsManagePatients
    {
        AddPatient = 1,    /**< Option to add a new patient */
        ViewPatient,       /**< Option to view a patient */
        SearchPatient,     /**< Option to search for a patient */
        SortPatient,       /**< Option to sort patients */
        ExitManagePatients /**< Option to exit patient management */
    };

    /**
     * @brief Enumeration for options to search for a patient.
     */
    enum OptionsManageSearchPatient
    {
        SearchByName = 1,     /**< Option to search patient by name */
        SearchByStatus,       /**< Option to search patient by status */
        SearchByTreatmentType /**< Option to search patient by treatment type */
    };

    /**
     * @brief Enumeration for options to sort patients.
     */
    enum OptionManageSortPatient
    {
        SortByAppointment = 1, /**< Option to sort by appointment */
        SortByLengthOfStay,    /**< Option to sort by length of stay */
        SortByPriority         /**< Option to sort by priority */
    };

    /**
     * @brief Enumeration for options to edit a patient.
     */
    enum OptionsEditPatient
    {
        EditName = 1,   /**< Option to edit patient name */
        EditStatus,     /**< Option to edit patient status */
        EditTreatment,  /**< Option to edit patient treatment */
        DeletePatient,  /**< Option to delete patient */
        ExitEditPatient /**< Option to exit patient editing */
    };

    /**
     * @brief Enumeration for options to manage treatments.
     */
    enum OptionsManageTreatment
    {
        AddTreatment = 1,   /**< Option to add a treatment */
        ViewTreatment,      /**< Option to view a treatment */
        ExitManageTreatment /**< Option to exit treatment management */
    };

    /**
     * @brief Enumeration for options to edit a treatment.
     */
    enum OptionsEditTreatment
    {
        EditTreatmentType = 1, /**< Option to edit treatment type */
        EditAppointment,       /**< Option to edit appointment */
        EditDayOfStay,         /**< Option to edit day of stay */
        EditPriority,          /**< Option to edit priority */
        DeleteTreatment,       /**< Option to delete treatment */
        ExitEditTreatment      /**< Option to exit treatment editing */
    };

    extern const int PatientManagerErrorPrefix; /**< Prefix for patient manager error codes */

    /**
     * @brief Enumeration of patient manager error codes.
     */
    enum PatientManagerError
    {
        NO_PATIENT_MANAGER_ERR, /**< No error */
        PATIENT_ID_NOT_FOUND,   /**< Patient ID not found */
        PATIENT_NAME_NOT_FOUND, /**< Patient name not found */
        PATIENT_LIST_EMPTY,     /**< Patient list is empty */
        TREATMENT_LIST_EMPTY    /**< Treatment list is empty */
    };

    extern const std::string PatientManagerErrorMessage[]; /**< Array of patient manager error messages */
    extern const int PatientManagerErrorMessageSize;       /**< Size of the patient manager error message array */

    /**
     * @brief Class to manage patients.
     */
    class PatientManager
    {
    public:
        /**
         * @brief Constructs a PatientManager with a reference to a client.
         * @param client Reference to the client.
         */
        PatientManager(HMS::Client &client);

        /**
         * @brief Manages patient operations.
         */
        void managePatients();

        /**
         * @brief Prints the list of patients.
         */
        void printPatientList();

        /**
         * @brief Prints a given list of patients.
         * @param patientList The list of patients to print.
         */
        void printPatientList(LinkedList<HMS::Patient> patientList);

        /**
         * @brief Prints details of a patient.
         * @param patient The patient whose details are to be printed.
         */
        void printPatientDetails(HMS::Patient patient);

        /**
         * @brief Prints details of a patient including their latest treatment.
         * @param patient The patient whose details are to be printed.
         * @param latestTreatment The latest treatment of the patient.
         */
        void printPatientDetails(HMS::Patient patient, HMS::Treatment latestTreatment);

        /**
         * @brief Prints the list of treatments for a patient.
         * @param patient The patient whose treatment list is to be printed.
         */
        void printTreatmentList(HMS::Patient patient);

        /**
         * @brief Prints details of a treatment.
         * @param treatment The treatment whose details are to be printed.
         */
        void printTreatmentDetails(HMS::Treatment treatment);

        /**
         * @brief Gets the current patient ID index.
         * @return The current patient ID index.
         */
        int getIdIndex();

        /**
         * @brief Generates a new patient ID.
         * @return The new patient ID.
         */
        int generatePatientId();

        /**
         * @brief Adds a patient to the patient list.
         * @param patient The patient to add.
         */
        void addPatient(HMS::Patient &patient);

        /**
         * @brief Gets the number of patients.
         * @return The number of patients.
         */
        int getPatientSize();

        /**
         * @brief Gets a patient by their index in the list.
         * @param index The index of the patient.
         * @return Pointer to the patient.
         */
        HMS::Patient *getPatient(int index);

        /**
         * @brief Gets a patient by matching patient object.
         * @param patient The patient to match.
         * @return Pointer to the matched patient.
         */
        HMS::Patient *getPatient(HMS::Patient patient);

        /**
         * @brief Gets a patient by their ID.
         * @param patient Reference to a pointer where the patient will be stored.
         * @param id The ID of the patient.
         * @return Error code indicating success or type of error.
         */
        ErrorCode getPatientById(HMS::Patient *&patient, int id);

        /**
         * @brief Gets an iterator for the patient list.
         * @return Iterator for the patient list.
         */
        Iterator<HMS::Patient> getPatientListIterator();

        /**
         * @brief Gets the error code for a specific patient manager error.
         * @param error The patient manager error.
         * @return The corresponding error code.
         */
        ErrorCode getErrorCode(PatientManagerError error);

        /**
         * @brief Gets the error code indicating no error.
         * @return The error code for no error.
         */
        ErrorCode noErrorCode();

    private:
        HMS::Client &client;                  /**< Reference to the client */
        LinkedList<HMS::Patient> patientList; /**< List of patients */
        int idIndex;                          /**< Current patient ID index */

        /**
         * @brief Manages the search operation for patients.
         * @param patientList Reference to the patient list.
         */
        void manageSearchPatient(LinkedList<HMS::Patient> &patientList);

        /**
         * @brief Manages the sort operation for patients.
         * @param patientList Reference to the patient list.
         */
        void manageSortPatient(LinkedList<HMS::Patient> &patientList);

        /**
         * @brief Edits a patient's details.
         * @param patient The patient to edit.
         */
        void editPatient(HMS::Patient &patient);

        /**
         * @brief Manages treatments for a patient.
         * @param patient The patient whose treatments are to be managed.
         */
        void manageTreatments(HMS::Patient &patient);

        /**
         * @brief Edits a treatment's details.
         * @param treatment The treatment to edit.
         * @param patient The patient whose treatment is being edited.
         */
        void editTreatment(HMS::Treatment &treatment, HMS::Patient &patient);

        /**
         * @brief Prompts the user to enter a patient's name.
         * @param patient The patient whose name is to be set.
         */
        void promptPatientName(HMS::Patient &patient);

        /**
         * @brief Prompts the user to enter a patient's status.
         * @param patient The patient whose status is to be set.
         */
        void promptPatientStatus(HMS::Patient &patient);

        /**
         * @brief Prompts the user to enter a treatment for a patient.
         * @param patient The patient whose treatment is to be set.
         */
        void promptPatientTreatment(HMS::Patient &patient);

        /**
         * @brief Prompts the user to enter a treatment type.
         * @param treatment The treatment whose type is to be set.
         */
        void promptTreatmentType(HMS::Treatment &treatment);

        /**
         * @brief Prompts the user to enter a treatment appointment.
         * @param treatment The treatment whose appointment is to be set.
         */
        void promptTreatmentAppointment(HMS::Treatment &treatment);

        /**
         * @brief Prompts the user to enter the number of days of stay for a treatment.
         * @param treatment The treatment whose days of stay is to be set.
         */
        void promptTreatmentDayOfStay(HMS::Treatment &treatment);

        /**
         * @brief Prompts the user to enter the priority of a treatment.
         * @param treatment The treatment whose priority is to be set.
         */
        void promptTreatmentPriority(HMS::Treatment &treatment);
    };
};
