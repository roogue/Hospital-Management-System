#include <iostream>
#include <string>
#include "cores/patient.h"

using namespace HMS;

bool Treatment::operator==(const Treatment &other)
{
    return appointment == other.appointment;
};
bool Treatment::operator!=(const Treatment &other)
{
    return appointment != other.appointment;
};
bool Treatment::operator>=(const Treatment &other)
{
    return appointment >= other.appointment;
};
bool Treatment::operator>(const Treatment &other)
{
    return appointment > other.appointment;
};
bool Treatment::operator<=(const Treatment &other)
{
    return appointment <= other.appointment;
};
bool Treatment::operator<(const Treatment &other)
{
    return appointment < other.appointment;
};

std::string Treatment::getTreatmentType()
{
    return this->type == TreatmentType::Other ? this->otherType : TreatmentTypeLookUp[this->type];
}

const std::string HMS::PatientStatusLookUp[] = {
    "Admitted",
    "Discharged",
};
const int HMS::PatientStatusSize = sizeof(HMS::PatientStatusLookUp) / sizeof(HMS::PatientStatusLookUp[0]);

const std::string HMS::TreatmentTypeLookUp[] = {
    "Symptomatic",
    "Constipation",
    "Diarrhoea",
    "Hemostasis",
    "Other",
};
const int HMS::TreatmentTypeSize = sizeof(HMS::TreatmentTypeLookUp) / sizeof(HMS::TreatmentTypeLookUp[0]);

Patient::Patient(int id)
    : id(id),
      name("Unknown"),
      status(Admitted){};

bool Patient::operator==(Patient &other)
{
    return this->id == other.id;
}

int Patient::getId()
{
    return this->id;
}

void Patient::setName(std::string name)
{
    this->name = name;
}
std::string Patient::getName()
{
    return this->name;
}

void Patient::setStatus(PatientStatus status)
{
    this->status = status;
};
PatientStatus Patient::getStatus()
{
    return this->status;
};

void Patient::addTreatment(Treatment treatment)
{
    this->treatments.addNode(treatment);
}
OrderedLinkedList<Treatment> Patient::getTreatments()
{
    return this->treatments;
};
Treatment Patient::getLatestTreatment()
{
    return this->treatments.getData(0);
}
