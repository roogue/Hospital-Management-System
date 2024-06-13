#include <iostream>
#include <string>
#include "cores/patient.h"

using namespace HMS;

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
      status(Admitted),
      treatments(),
      admissions(),
      discharges(){};

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
std::string Patient::getFormattedStatus()
{
    return HMS::PatientStatusLookUp[this->getStatus()];
}

void Patient::addTreatment(Treatment treatment)
{
    this->treatments.addNode(treatment);
}
void Patient::deleteTreatment(Treatment treatment)
{
    this->treatments.deleteNode(treatment);
}
int Patient::getTreatmentsSize()
{
    return this->treatments.getSize();
}
Treatment *Patient::getTreatment(int index)
{
    return this->treatments.getData(index);
}
Treatment *Patient::getLatestTreatment()
{
    if (treatments.isEmpty())
    {
        return nullptr;
    }

    return this->treatments.getData(0);
}

void Patient::addAdmissionDate(Handler::Date date)
{
    this->admissions.addNode(date);
}
void Patient::addDischargeDate(Handler::Date date)
{
    this->discharges.addNode(date);
}