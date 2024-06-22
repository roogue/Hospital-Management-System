#include <iostream>
#include "handlers/inputHandler.h"

namespace HMS
{
    /**
     * @brief Enumeration for the type of treatment.
     */
    enum TreatmentType
    {
        Symptomatic,  /**< Symptomatic treatment */
        Constipation, /**< Treatment for constipation */
        Diarrhoea,    /**< Treatment for diarrhoea */
        Hemostasis,   /**< Hemostasis treatment */
        Other         /**< Other types of treatment */
    };

    /**
     * @brief Lookup array for treatment type strings.
     */
    extern const std::string TreatmentTypeLookUp[];

    /**
     * @brief Size of the treatment type lookup array.
     */
    extern const int TreatmentTypeSize;

    /**
     * @brief Class representing a treatment in the Hospital Management System.
     */
    class Treatment
    {
    public:
        /**
         * @brief Constructor for the Treatment class.
         */
        Treatment();

        /**
         * @brief Sets the type of the treatment.
         * @param treatment The treatment type to set.
         */
        void setTreatmentType(TreatmentType treatment);

        /**
         * @brief Gets the type of the treatment.
         * @return The type of the treatment.
         */
        TreatmentType getTreatmentType();

        /**
         * @brief Sets the type of the treatment when it is of type Other.
         * @param treatment The string describing the other treatment type.
         */
        void setOtherTreatmentType(std::string treatment);

        /**
         * @brief Gets the type of the treatment when it is of type Other.
         * @return The string describing the other treatment type.
         */
        std::string getOtherTreatmentType();

        /**
         * @brief Gets the formatted treatment type as a string.
         * @return The formatted treatment type.
         */
        std::string getFormattedTreatmentType();

        /**
         * @brief Sets the appointment date for the treatment.
         * @param appointment The appointment date to set.
         */
        void setAppointment(Handler::Date appointment);

        /**
         * @brief Gets the appointment date for the treatment.
         * @return The appointment date.
         */
        Handler::Date getAppointment();

        /**
         * @brief Sets the number of days of stay for the treatment.
         * @param dayOfStay The number of days of stay to set.
         */
        void setDayOfStay(int dayOfStay);

        /**
         * @brief Gets the number of days of stay for the treatment.
         * @return The number of days of stay.
         */
        int getDayOfStay();

        /**
         * @brief Sets the priority of the treatment.
         * @param priority The priority to set.
         */
        void setPriority(int priority);

        /**
         * @brief Gets the priority of the treatment.
         * @return The priority.
         */
        int getPriority();

        /**
         * @brief Set treatment as completed.
         */
        void setCompleted();

        /**
         * @brief Gets the completeness of the treatment
         * @return True if the treatment is completed, false otherwise
         */
        bool isCompleted();

        /**
         * @brief Equality operator to compare two treatments.
         * @param other The other treatment to compare.
         * @return True if the treatments are equal, false otherwise.
         */
        bool operator==(const Treatment &other);

        /**
         * @brief Inequality operator to compare two treatments.
         * @param other The other treatment to compare.
         * @return True if the treatments are not equal, false otherwise.
         */
        bool operator!=(const Treatment &other);

        /**
         * @brief Greater than or equal operator to compare two treatments.
         * @param other The other treatment to compare.
         * @return True if this treatment is greater than or equal to the other, false otherwise.
         */
        bool operator>=(const Treatment &other);

        /**
         * @brief Greater than operator to compare two treatments.
         * @param other The other treatment to compare.
         * @return True if this treatment is greater than the other, false otherwise.
         */
        bool operator>(const Treatment &other);

        /**
         * @brief Less than or equal operator to compare two treatments.
         * @param other The other treatment to compare.
         * @return True if this treatment is less than or equal to the other, false otherwise.
         */
        bool operator<=(const Treatment &other);

        /**
         * @brief Less than operator to compare two treatments.
         * @param other The other treatment to compare.
         * @return True if this treatment is less than the other, false otherwise.
         */
        bool operator<(const Treatment &other);

    private:
        TreatmentType type;        /**< The type of the treatment */
        std::string otherType;     /**< The description for 'Other' treatment type */
        Handler::Date appointment; /**< The appointment date for the treatment */
        int dayOfStay;             /**< The number of days of stay for the treatment */
        int priority;              /**< The priority of the treatment */
        bool completed;            /**< The completeness of the treatment */
    };
}
