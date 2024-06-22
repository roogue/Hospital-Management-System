#pragma once

#include <iostream>
#include "handlers/inputHandler.h"
#include "structs/orderedLinkedList.h"
#include "cores/treatment.h"

namespace HMS
{
    /**
     * @brief Enumeration for the status of a patient.
     */
    enum PatientStatus
    {
        Admitted,  /**< The patient is currently admitted. */
        Discharged /**< The patient has been discharged. */
    };

    /**
     * @brief Lookup array for patient status strings.
     */
    extern const std::string PatientStatusLookUp[];

    /**
     * @brief Size of the patient status lookup array.
     */
    extern const int PatientStatusSize;

    /**
     * @brief Class representing a patient in the Hospital Management System.
     */
    class Patient
    {
    public:
        /**
         * @brief Constructor for the Patient class.
         * @param id The ID of the patient, default is 0.
         */
        Patient(int id = 0);

        /**
         * @brief Equality operator to compare two patients.
         * @param other The other patient to compare.
         * @return True if the patients are equal, false otherwise.
         */
        bool operator==(Patient &other);
        /**
         * @brief Greater Than operator to compare two patients.
         * @param other The other patient to compare.
         * @return True if the patients are equal, false otherwise.
         */
        bool operator>(Patient &other);
        /**
         * @brief Less Than operator to compare two patients.
         * @param other The other patient to compare.
         * @return True if the patients are equal, false otherwise.
         */
        bool operator<(Patient &other);
        /**
         * @brief Greater Than or Equal To operator to compare two patients.
         * @param other The other patient to compare.
         * @return True if the patients are equal, false otherwise.
         */
        bool operator>=(Patient &other);
        /**
         * @brief Less Than or Equal To operator to compare two patients.
         * @param other The other patient to compare.
         * @return True if the patients are equal, false otherwise.
         */
        bool operator<=(Patient &other);

        /**
         * @brief Gets the ID of the patient.
         * @return The ID of the patient.
         */
        int getId();

        /**
         * @brief Sets the name of the patient.
         * @param name The name to set.
         */
        void setName(std::string name);

        /**
         * @brief Gets the name of the patient.
         * @return The name of the patient.
         */
        std::string getName();

        /**
         * @brief Searches for a patient by name.
         * @param patient The patient to search in.
         * @param name The name to search for.
         * @return True if the name matches, false otherwise.
         */
        static bool searchName(Patient &patient, std::string name);

        /**
         * @brief Sets the status of the patient.
         * @param status The status to set.
         */
        void setStatus(PatientStatus status);

        /**
         * @brief Gets the status of the patient.
         * @return The status of the patient.
         */
        PatientStatus getStatus();

        /**
         * @brief Gets the formatted status of the patient as a string.
         * @return The formatted status of the patient.
         */
        std::string getFormattedStatus();

        /**
         * @brief Searches for a patient by status.
         * @param patient The patient to search in.
         * @param status The status to search for.
         * @return True if the status matches, false otherwise.
         */
        static bool searchStatus(Patient &patient, HMS::PatientStatus status);

        /**
         * @brief Adds a treatment to the patient's treatment list.
         * @param treatment The treatment to add.
         */
        void addTreatment(Treatment treatment);

        /**
         * @brief Deletes a treatment from the patient's treatment list.
         * @param treatment The treatment to delete.
         */
        void deleteTreatment(Treatment treatment);

        /**
         * @brief Gets the number of treatments the patient has.
         * @return The number of treatments.
         */
        int getTreatmentsSize();

        /**
         * @brief Gets a treatment by index.
         * @param index The index of the treatment.
         * @return Pointer to the treatment.
         */
        Treatment *getTreatment(int index);

        /**
         * @brief Gets the latest treatment of the patient.
         * @return Pointer to the latest treatment.
         */
        Treatment *getLatestTreatment();

        /**
         * @brief Searches for a treatment by type.
         * @param patient The patient to search in.
         * @param treatmentType The treatment type to search for.
         * @return True if the treatment type matches, false otherwise.
         */
        static bool searchTreatmentType(Patient &patient, std::string treatmentType);

        /**
         * @brief Static function to compare the treatment appointments of two patients.
         * @param patient The first patient.
         * @param otherPatient The second patient.
         * @return True if the first patient's treatment appointment is earlier, false otherwise.
         */
        static bool compareTreatmentAppointment(Patient &patient, Patient &otherPatient);

        /**
         * @brief Static function to compare the days of stay for treatment between two patients.
         * @param patient The first patient.
         * @param otherPatient The second patient.
         * @return True if the first patient has fewer days of stay, false otherwise.
         */
        static bool compareTreatmentDayOfStay(Patient &patient, Patient &otherPatient);

        /**
         * @brief Static function to compare the treatment priority between two patients.
         * @param patient The first patient.
         * @param otherPatient The second patient.
         * @return True if the first patient has higher treatment priority, false otherwise.
         */
        static bool compareTreatmentPriority(Patient &patient, Patient &otherPatient);

        /**
         * @brief Adds an admission date to the patient's record.
         * @param date The admission date to add.
         */
        void addAdmissionDate(Handler::Date date);

        /**
         * @brief Adds a discharge date to the patient's record.
         * @param date The discharge date to add.
         */
        void addDischargeDate(Handler::Date date);

        /**
         * @brief Gets an iterator for the patient's treatments.
         * @return An iterator for the treatments.
         */
        Iterator<Treatment> getTreatmentIterator();

        /**
         * @brief Gets an iterator for the patient's admissions.
         * @return An iterator for the admissions.
         */
        Iterator<Handler::Date> getAdmissionsIterator();

        /**
         * @brief Gets an iterator for the patient's discharges.
         * @return An iterator for the discharges.
         */
        Iterator<Handler::Date> getDischargesIterator();

    private:
        unsigned int id;                             /**< The ID of the patient */
        std::string name;                            /**< The name of the patient */
        PatientStatus status;                        /**< The status of the patient */
        OrderedLinkedList<Treatment> treatments;     /**< The list of treatments for the patient */
        OrderedLinkedList<Handler::Date> admissions; /**< The list of admission dates for the patient */
        OrderedLinkedList<Handler::Date> discharges; /**< The list of discharge dates for the patient */
    };
}