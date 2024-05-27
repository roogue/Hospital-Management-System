#pragma once

#include <iostream>
#include "handlers/inputHandler.h"
#include "structs/orderedLinkedList.h"

namespace HMS
{
    enum TreatmentType
    {
        Symptomatic,
        Constipation,
        Diarrhoea,
        Hemostasis,
        Other
    };

    extern const std::string TreatmentTypeLookUp[];
    extern const int TreatmentTypeSize;
    struct Treatment
    {
        TreatmentType type;
        std::string otherType;
        Handler::Date appointment;
        int dayOfStay;
        int priority;

        bool operator==(const Treatment &other);
        bool operator!=(const Treatment &other);
        bool operator>=(const Treatment &other);
        bool operator>(const Treatment &other);
        bool operator<=(const Treatment &other);
        bool operator<(const Treatment &other);

        std::string getTreatmentType();
    };

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

        void addTreatment(Treatment treatment);
        OrderedLinkedList<Treatment> getTreatments();
        Treatment getLatestTreatment();

    private:
        unsigned int id;
        std::string name;
        PatientStatus status;
        OrderedLinkedList<Treatment> treatments;
        OrderedLinkedList<Handler::Date> admissions;
        OrderedLinkedList<Handler::Date> discharges;
    };
}