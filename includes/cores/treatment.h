#include <iostream>
#include "handlers/inputHandler.h"

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

    class Treatment
    {
    public:
        Treatment();
        void setTreatmentType(TreatmentType treatment);
        TreatmentType getTreatmentType();

        void setOtherTreatmentType(std::string treatment);
        std::string getOtherTreatmentType();

        std::string getFormattedTreatmentType();

        void setAppointment(Handler::Date appointment);
        Handler::Date getAppointment();

        void setDayOfStay(int dayOfStay);
        int getDayOfStay();

        void setPriority(int priority);
        int getPriority();

        void setCompleted();
        bool isCompleted();

        bool operator==(const Treatment &other);
        bool operator!=(const Treatment &other);
        bool operator>=(const Treatment &other);
        bool operator>(const Treatment &other);
        bool operator<=(const Treatment &other);
        bool operator<(const Treatment &other);

    private:
        TreatmentType type;
        std::string otherType;
        Handler::Date appointment;
        int dayOfStay;
        int priority;
        bool completed;
    };
}