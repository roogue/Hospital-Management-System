#include "cores/treatment.h"

using namespace HMS;

Treatment::Treatment()
    : type(TreatmentType::Symptomatic),
      otherType(""),
      appointment({0, 0, 0}),
      dayOfStay(0),
      priority(0){};

void Treatment::setTreatmentType(TreatmentType treatment)
{
    this->type = treatment;
};
TreatmentType Treatment::getTreatmentType()
{
    return this->type;
};

void Treatment::setOtherTreatmentType(std::string treatment)
{
    this->otherType = treatment;
};
std::string Treatment::getOtherTreatmentType()
{
    return this->otherType;
};

std::string Treatment::getFormattedTreatmentType()
{
    return this->type == TreatmentType::Other ? this->otherType : TreatmentTypeLookUp[this->type];
};

void Treatment::setAppointment(Handler::Date appointment)
{
    this->appointment = appointment;
};
Handler::Date Treatment::getAppointment()
{
    return this->appointment;
};

void Treatment::setDayOfStay(int dayOfStay)
{
    this->dayOfStay = dayOfStay;
};
int Treatment::getDayOfStay()
{
    return this->dayOfStay;
};

void Treatment::setPriority(int priority)
{
    this->priority = priority;
};
int Treatment::getPriority()
{
    return this->priority;
};

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