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

        int getId();

        void setName(std::string name);
        std::string getName();

        void setStatus(PatientStatus status);
        PatientStatus getStatus();
        std::string getFormattedStatus();

        void addTreatment(Treatment treatment);
        void deleteTreatment(Treatment treatment);
        int getTreatmentsSize();
        Treatment *getTreatment(int index);
        Treatment *getLatestTreatment();

    private:
        unsigned int id;
        std::string name;
        PatientStatus status;
        OrderedLinkedList<Treatment> treatments;
        OrderedLinkedList<Handler::Date> admissions;
        OrderedLinkedList<Handler::Date> discharges;
    };
}