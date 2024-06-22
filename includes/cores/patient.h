#pragma once

#include <iostream>
#include "handlers/inputHandler.h"
#include "structs/orderedLinkedList.h"
#include "cores/treatment.h"

namespace HMS
{
    enum PatientStatus
    {
        Admitted,
        Discharged
    };
    extern const std::string PatientStatusLookUp[];
    extern const int PatientStatusSize;

    class Patient
    {
    public:
        Patient(int id = 0);
        bool operator==(Patient &other);
        bool operator>(Patient &other);
        bool operator<(Patient &other);
        bool operator>=(Patient &other);
        bool operator<=(Patient &other);

        int getId();

        void setName(std::string name);
        std::string getName();
        static bool searchName(Patient &patient, std::string name);

        void setStatus(PatientStatus status);
        PatientStatus getStatus();
        std::string getFormattedStatus();
        static bool searchStatus(Patient &patient, HMS::PatientStatus status);

        void addTreatment(Treatment treatment);
        void deleteTreatment(Treatment treatment);
        int getTreatmentsSize();
        Treatment *getTreatment(int index);
        Treatment *getLatestTreatment();
        static bool searchTreatmentType(Patient &patient, std::string treatmentType);
        static bool compareTreatmentAppointment(Patient &patient, Patient &otherPatient);
        static bool compareTreatmentDayOfStay(Patient &patient, Patient &otherPatient);
        static bool compareTreatmentPriority(Patient &patient, Patient &otherPatient);

        void addAdmissionDate(Handler::Date date);
        void addDischargeDate(Handler::Date date);

        Iterator<Treatment> getTreatmentIterator();
        Iterator<Handler::Date> getAdmissionsIterator();
        Iterator<Handler::Date> getDischargesIterator();

    private:
        unsigned int id;
        std::string name;
        PatientStatus status;
        OrderedLinkedList<Treatment> treatments;
        OrderedLinkedList<Handler::Date> admissions;
        OrderedLinkedList<Handler::Date> discharges;
    };
}