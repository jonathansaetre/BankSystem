#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
#include <util.cpp>
#include <QSqlQueryModel>

class DbManager {
public:
    static DbManager* getInstance();
    static void close();

    bool addCustomer(Customer c);
    bool addAccount(Account c);
    bool addTransaction(Transaction c);

    bool updateCustomer(Customer c);
    bool updateAccount(Account c);
    bool updateTransaction(Transaction c);

    bool deleteCustomer(Customer c);
    bool deleteAccount(Account c);
    bool deleteTransaction(Transaction c);

    Customer fetchCustomer(Customer c);
    Account fetchAccount(Account c);
    Transaction fetchTransaction(Transaction c);

    QSqlQueryModel* fetchCustomerList();
    QSqlQueryModel* fetchAccountList(QString customerID);
    QSqlQueryModel* fetchTransactionList(QString customerID);
    QSqlQuery fetchCustomerFTSlist(QString s);

    bool existsSSN(QString ssn);

private:
    DbManager();
    static DbManager *instance;
    QSqlDatabase db;
    bool existsQuery(QString q);
    bool addCustomerFST(Customer r);
    bool updateCustomerFST(Customer r);
    bool deleteCustomerFST(Customer r);
};

#endif // DBMANAGER_H
