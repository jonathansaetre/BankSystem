#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
#include <util.cpp>
#include <QSqlQueryModel>
#include <QStandardItemModel>

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
    QStandardItemModel* fetchStandardCustomerList(int state = 1);
    QSqlQueryModel* fetchQueryCustomerList(int state = 1);
    QSqlQuery searchCustomer(QString searchText, int state = 1);
    QSqlQueryModel* fetchAccountList(QString customerID);
    QStandardItemModel* fetchTransactionList(QString customerID = "");
    bool existsSSN(QString ssn);

private:
    DbManager();
    static DbManager *instance;
    QSqlDatabase db;
    bool addCustomerFST(Customer r);
    bool updateCustomerFST(Customer r);
    bool deleteCustomerFST(Customer r);
    bool runQuery(QString queryString);
    bool executeTransfer(Transaction r);
    void error(QString s, QSqlQuery query);
};

#endif // DBMANAGER_H
