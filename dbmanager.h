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
private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
