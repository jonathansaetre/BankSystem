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

    Customer addCustomer(Customer c);
    bool addAccount(Account c);
    bool addTransaction(Transaction c);

    bool updateCustomer(Customer c);
    bool updateAccount(Account c);
    bool updateTransaction(Transaction c);

    bool deleteCustomer(Customer c);
    bool deleteAccount(Account c);
    bool deleteTransaction(Transaction c);

    Customer fetchCustomer(QString id);
    Account fetchAccount(QString id);
    Transaction fetchTransaction(QString id);

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
    bool runQuery(QString queryString);
    bool executeTransfer(Transaction r);
    bool existsAccountNr(QString accountNr);
    QString getAccountnr();
};

#endif // DBMANAGER_H
