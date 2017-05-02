#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
#include <objects.cpp>
#include <QSqlQueryModel>

class DbManager {
public:
    static DbManager* getInstance();
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
    QSqlQueryModel* fetchAccountList();
    QSqlQueryModel* fetchTransactionList();

private:
    DbManager();
    static DbManager *instance;
    QSqlDatabase db;
    bool existsRecordQuery(QString q, QString id);
};

#endif // DBMANAGER_H
