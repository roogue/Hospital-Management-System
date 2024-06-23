#include <iostream>
#include <string>
#include "cores/patient.h"
#include "handlers/inputHandler.h"

using namespace HMS;

// Lookup arrays for patient statuses and treatment types
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
      discharges() {};

bool Patient::operator==(Patient &other)
{
    return this->id == other.id;
}

bool Patient::operator>(Patient &other)
{
    return this->id > other.id;
}

bool Patient::operator<(Patient &other)
{
    return this->id < other.id;
}

bool Patient::operator>=(Patient &other)
{
    return this->id >= other.id;
}

bool Patient::operator<=(Patient &other)
{
    return this->id <= other.id;
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
bool Patient::searchName(Patient &patient, std::string name)
{
    return name == patient.getName();
};

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
bool Patient::searchStatus(Patient &patient, HMS::PatientStatus status)
{
    return status == patient.getStatus();
};

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

// Static function to search for a patient by treatment type for searching algorithm
bool Patient::searchTreatmentType(Patient &patient, std::string treatmentType)
{
    HMS::Treatment *latestTreatment = patient.getLatestTreatment();
    if (latestTreatment != nullptr || latestTreatment->isCompleted())
    {
        return treatmentType == latestTreatment->getFormattedTreatmentType();
    }

    return false;
};

// Static function to compare two patients by their latest treatment appointment date for sorting algorithm
bool Patient::compareTreatmentAppointment(Patient &patient, Patient &otherPatient)
{
    HMS::Treatment *latestTreatment = patient.getLatestTreatment();
    if (latestTreatment == nullptr || latestTreatment->isCompleted())
    {
        return false;
    }

    HMS::Treatment *otherLatestTreatment = otherPatient.getLatestTreatment();
    if (otherLatestTreatment == nullptr || otherLatestTreatment->isCompleted())
    {
        return true;
    }

    return latestTreatment->getAppointment() < otherLatestTreatment->getAppointment();
};

// Static function to compare two patients by their latest treatment day of stay for sorting algorithm
bool Patient::compareTreatmentDayOfStay(Patient &patient, Patient &otherPatient)
{
    HMS::Treatment *latestTreatment = patient.getLatestTreatment();
    if (latestTreatment == nullptr || latestTreatment->isCompleted())
    {
        return false;
    }

    HMS::Treatment *otherLatestTreatment = otherPatient.getLatestTreatment();
    if (otherLatestTreatment == nullptr || otherLatestTreatment->isCompleted())
    {
        return true;
    }

    return latestTreatment->getDayOfStay() < otherLatestTreatment->getDayOfStay();
};

// Static function to compare two patients by their latest treatment priority for sorting algorithm
bool Patient::compareTreatmentPriority(Patient &patient, Patient &otherPatient)
{
    HMS::Treatment *latestTreatment = patient.getLatestTreatment();
    if (latestTreatment == nullptr || latestTreatment->isCompleted())
    {
        return false;
    }

    HMS::Treatment *otherLatestTreatment = otherPatient.getLatestTreatment();
    if (otherLatestTreatment == nullptr || otherLatestTreatment->isCompleted())
    {
        return true;
    }

    return latestTreatment->getPriority() > otherLatestTreatment->getPriority();
}

void Patient::addAdmissionDate(Handler::Date date)
{
    this->admissions.addNode(date);
}
void Patient::addDischargeDate(Handler::Date date)
{
    this->discharges.addNode(date);
}

Iterator<HMS::Treatment> Patient::getTreatmentIterator()
{
    return this->treatments.iterate();
}

Iterator<Handler::Date> Patient::getAdmissionsIterator()
{
    return this->admissions.iterate();
}

Iterator<Handler::Date> Patient::getDischargesIterator()
{
    return this->discharges.iterate();
}