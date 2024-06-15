#pragma once
#include "cores/client.h"

// Forward declaration
namespace HMS
{
    class Client;
}

namespace Manager
{
    struct Event
    {
        Handler::Date date;
        std::string description;

        bool operator<(Event &other);
    };

    enum OptionsManageReport
    {
        GenerateOverallReport = 1,
        GenerateReportForPatient,
        ExitManageReport
    };

    extern const int ReportManagerErrorPrefix;
    enum ReportManagerError
    {
        NO_REPORT_MANAGER_ERR,
        RM_PATIENT_LIST_EMPTY,
    };
    extern const std::string ReportManagerErrorMessage[];
    extern const int ReportManagerErrorMessageSize;

    class ReportManager
    {
    public:
        ReportManager(HMS::Client &client);
        void manageReport();

        ErrorCode getErrorCode(ReportManagerError error);
        ErrorCode noErrorCode();

    private:
        HMS::Client &client;
    };
}