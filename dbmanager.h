#ifndef DBMANAGER_H
#define DBMANAGER_H
using namespace std;
#include <QString>
#include <QSqlDatabase>
#include <objects.cpp>

class DbManager {
public:
    DbManager();
    bool addCustomer(Customer c);
    bool updateCustomer(Customer c);
    bool deleteCustomer(Customer c);
    Customer fetchCustomer(Customer c);
private:
    QSqlDatabase db;
    bool existsQuery(QString q, QString id);
};

#endif // DBMANAGER_H
