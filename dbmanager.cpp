#include <dbmanager.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QSqlRecord>

DbManager::DbManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BankingSystem.db");
    if (!db.open() || db.tables().empty()) qDebug() << "Error: connection with database fail";
}

bool DbManager::addCustomer(const Customer c) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Customer (name, ssn, phone, address, email) VALUES (:name, :ssn, :phone, :address, :email)");
    query.bindValue(":name", c.name);
    query.bindValue(":ssn", c.ssn);
    query.bindValue(":phone", c.phone);
    query.bindValue(":address", c.address);
    query.bindValue(":email", c.email);
    if(query.exec()) return true;
    qDebug() << query.executedQuery();
    qDebug() << "addCustomer error:  " << query.lastError();
    return false;
}

bool DbManager::updateCustomer(const Customer c) {
    QSqlQuery query(db);
    if(!existsQuery("SELECT * FROM Customer WHERE id=:id", c.id)) return false;
    query.prepare("UPDATE Customer SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email WHERE id=:id");
    query.bindValue(":id", c.id);
    query.bindValue(":name", c.name);
    query.bindValue(":ssn", c.ssn);
    query.bindValue(":phone", c.phone);
    query.bindValue(":address", c.address);
    query.bindValue(":email", c.email);
    if(query.exec()) return true;
    qDebug() << "updateCustomer error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

bool DbManager::deleteCustomer(const Customer c) {
    QSqlQuery query(db);
    if(!existsQuery("SELECT * FROM Customer where id=:id", c.id)) return false;
    query.prepare("DELETE from Customer where id=:id");
    query.bindValue(":id", c.id);
    if(query.exec()) return true;
    qDebug() << "deleteCustomer error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

Customer DbManager::fetchCustomer(const Customer c) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer WHERE id=:id");
    query.bindValue(":id", c.id);
    Customer getC;
    if(query.exec()) {
        if(!query.next() && !query.isSelect() && !query.first()) return getC;
        QSqlRecord record = query.record();
        getC.id = record.value("id").toString();
        getC.name = record.value("name").toString();
        getC.ssn = query.value("ssn").toString();
        getC.phone = query.value("phone").toString();
        getC.address = query.value("address").toString();
        getC.email = query.value("email").toString();
    } else {
        qDebug() << "fetchCustomer error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return getC;
}

bool DbManager::existsQuery(const QString q, QString id) {
    QSqlQuery query(db);
    query.prepare(q);
    query.bindValue(":id", id);
    if(query.exec()) {
        if(query.isSelect() && query.next()) return true;
        else return false;
    }
    qDebug() << "existsQuery error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}
