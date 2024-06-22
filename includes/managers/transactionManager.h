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
    /**
     * @brief Enumeration for options to manage transactions.
     */
    enum OptionsManageTransaction
    {
        DischargePatient = 1, /**< Option to discharge a patient */
        SortTransaction,      /**< Option to sort transactions */
        ExitManageTransaction /**< Option to exit transaction management */
    };

    /**
     * @brief Enumeration for options to sort transactions.
     */
    enum OptionsSortTransaction
    {
        SortTransactionByAppointment = 1, /**< Option to sort transactions by appointment */
        SortTransactionByLengthOfStay,    /**< Option to sort transactions by length of stay */
        SortTransactionByPriority         /**< Option to sort transactions by priority */
    };

    extern const int TransactionManagerErrorPrefix; /**< Prefix for transaction manager error codes */

    /**
     * @brief Enumeration of transaction manager error codes.
     */
    enum TransactionManagerError
    {
        NO_TRANSACTION_MANAGER_ERR, /**< No error */
        NO_ADMITTED_PATIENT         /**< No admitted patients found */
    };

    extern const std::string TransactionManagerErrorMessage[]; /**< Array of transaction manager error messages */
    extern const int TransactionManagerErrorMessageSize;       /**< Size of the transaction manager error message array */

    /**
     * @brief Class to manage transactions.
     */
    class TransactionManager
    {
    public:
        /**
         * @brief Constructs a TransactionManager with a reference to a client.
         * @param client Reference to the client.
         */
        TransactionManager(HMS::Client &client);

        /**
         * @brief Manages transaction operations.
         */
        void manageTransaction();

        /**
         * @brief Manages sorting of transactions.
         */
        void manageSortTransaction();

        /**
         * @brief Prints the list of transactions.
         */
        void printTransactionList();

        /**
         * @brief Gets the error code for a specific transaction manager error.
         * @param error The transaction manager error.
         * @return The corresponding error code.
         */
        ErrorCode getErrorCode(TransactionManagerError error);

        /**
         * @brief Gets the error code indicating no error.
         * @return The error code for no error.
         */
        ErrorCode noErrorCode();

    private:
        HMS::Client &client;                 /**< Reference to the client */
        Queue<HMS::Patient> transactionList; /**< Queue of patient transactions */

        /**
         * @brief Resets the transaction list.
         */
        void resetTransactionList();
    };
}
