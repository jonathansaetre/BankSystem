#include <dbmanager.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    qDebug() << db.databaseName();
    qDebug() << db.tables();
    db.open();
    if (!db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

bool DbManager::addCustomer(const Customer c) {
    bool success = false;
    // you should check if args are ok first...
    QSqlQuery query(db);
//    query.prepare("INSERT INTO Customer (id,name,ssn,phone,address,email) VALUES ('1','ss','asdasd','sdsd','ssssss','sd');");
//    query.prepare("INSERT INTO Customer (id,name,ssn,phone,address,email) VALUES ('1', '" + c.name + "','" + c.ssn + "','" + c.phone + "','" + c.address + "','" + c.email +"')");
    query.prepare("INSERT INTO Customer (name) VALUES (?name)");
//    query.bindValue(":id", '1');
    query.bindValue("?name", c.name);
//    query.bindValue("ssn", c.ssn);
//    query.bindValue("phone", c.phone);
//    query.bindValue("address", c.address);
//    query.bindValue("email", c.email);
    if(query.exec()) success = true;
    else
    {
        qDebug() << query.executedQuery();
        qDebug() << QSqlDatabase::drivers();
        qDebug() << "addCustomer error:  " << query.lastError();
    }
    return success;
}
