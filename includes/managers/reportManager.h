#pragma once
#include "cores/client.h"

// Forward declaration
namespace HMS
{
    class Client;
}

namespace Manager
{
    /**
     * @brief Struct representing an event with a date and description.
     */
    struct Event
    {
        Handler::Date date;      /**< Date of the event */
        std::string description; /**< Description of the event */

        /**
         * @brief Less-than operator for comparing events by date.
         * @param other Another event to compare with.
         * @return True if this event is earlier than the other event.
         */
        bool operator<(Event &other);
    };

    /**
     * @brief Enumeration for options to manage reports.
     */
    enum OptionsManageReport
    {
        GenerateOverallReport = 1, /**< Option to generate an overall report */
        GenerateReportForPatient,  /**< Option to generate a report for a specific patient */
        ExitManageReport           /**< Option to exit report management */
    };

    extern const int ReportManagerErrorPrefix; /**< Prefix for report manager error codes */

    /**
     * @brief Enumeration of report manager error codes.
     */
    enum ReportManagerError
    {
        NO_REPORT_MANAGER_ERR, /**< No error */
        RM_PATIENT_LIST_EMPTY, /**< Patient list is empty */
    };

    extern const std::string ReportManagerErrorMessage[]; /**< Array of report manager error messages */
    extern const int ReportManagerErrorMessageSize;       /**< Size of the report manager error message array */

    /**
     * @brief Class to manage reports.
     */
    class ReportManager
    {
    public:
        /**
         * @brief Constructs a ReportManager with a reference to a client.
         * @param client Reference to the client.
         */
        ReportManager(HMS::Client &client);

        /**
         * @brief Manages report generation operations.
         */
        void manageReport();

        /**
         * @brief Gets the error code for a specific report manager error.
         * @param error The report manager error.
         * @return The corresponding error code.
         */
        ErrorCode getErrorCode(ReportManagerError error);

        /**
         * @brief Gets the error code indicating no error.
         * @return The error code for no error.
         */
        ErrorCode noErrorCode();

    private:
        HMS::Client &client; /**< Reference to the client */
    };
}
