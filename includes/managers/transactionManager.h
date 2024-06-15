#pragma once

#include <iostream>
#include "structs/queue.h"
#include "cores/client.h"
#include "cores/patient.h"

// Forward declaration
namespace HMS
{
    class Client;
}

namespace Manager
{
    enum OptionsManageTransaction
    {
        DischargePatient = 1,
        SortTransaction,
        ExitManageTransaction
    };
    enum OptionsSortTransaction
    {
        SortTransactionByAppointment = 1,
        SortTransactionByLengthOfStay,
        SortTransactionByPriority,
    };

    extern const int TransactionManagerErrorPrefix;
    enum TransactionManagerError
    {
        NO_TRANSACTION_MANAGER_ERR,
        NO_ADMITTED_PATIENT
    };
    extern const std::string TransactionManagerErrorMessage[];
    extern const int TransactionManagerErrorMessageSize;

    class TransactionManager
    {
    public:
        TransactionManager(HMS::Client &client);
        void manageTransaction();
        void manageSortTransaction();
        void printTransactionList();

        ErrorCode getErrorCode(TransactionManagerError error);
        ErrorCode noErrorCode();

    private:
        HMS::Client &client;
        Queue<HMS::Patient> transactionList;

        void resetTransactionList();
    };
}