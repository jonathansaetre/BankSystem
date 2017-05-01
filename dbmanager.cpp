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

bool DbManager::addCustomer(const Customer r) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Customer (name, ssn, phone, address, email) VALUES (:name, :ssn, :phone, :address, :email)");
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    if(query.exec()) return true;
    qDebug() << query.executedQuery();
    qDebug() << "addCustomer error:  " << query.lastError();
    return false;
}

bool DbManager::addAccount(const Account r) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Account (name, customerid, balance) VALUES (:name, :customerid, :balance)");
    query.bindValue(":name", r.name);
    query.bindValue(":customerid", r.customerID);
    query.bindValue(":balance", r.balance);
    if(query.exec()) return true;
    qDebug() << query.executedQuery();
    qDebug() << "addAccount error:  " << query.lastError();
    return false;
}

bool DbManager::addTransaction(const Transaction r) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Transaction (fromid, toid, amount, date) VALUES (:fromid, :toid, :amount, :date)");
    query.bindValue(":fromid", r.fromID);
    query.bindValue(":toid", r.toID);
    query.bindValue(":amount", r.amount);
    query.bindValue(":date", r.date);
    if(query.exec()) return true;
    qDebug() << query.executedQuery();
    qDebug() << "addTransaction error:  " << query.lastError();
    return false;
}

bool DbManager::updateCustomer(const Customer r) {
    QSqlQuery query(db);
    if(!existsRecordQuery("SELECT * FROM Customer WHERE id=:id", r.id)) return false;
    query.prepare("UPDATE Customer SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    if(query.exec()) return true;
    qDebug() << "updateCustomer error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

bool DbManager::updateAccount(const Account r) {
    QSqlQuery query(db);
    if(!existsRecordQuery("SELECT * FROM Account WHERE id=:id", r.id)) return false;
    query.prepare("UPDATE Account SET name=:name, customerid=:customerid, balance=:balance WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.customerID);
    query.bindValue(":phone", r.balance);
    if(query.exec()) return true;
    qDebug() << "updateAccount error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

bool DbManager::updateTransaction(const Transaction r) {
    QSqlQuery query(db);
    if(!existsRecordQuery("SELECT * FROM Transaction WHERE id=:id", r.id)) return false;
    query.prepare("UPDATE Transaction SET fromid=:fromid, toid=:toid, amount=:amount, date=:date WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":fromid", r.fromID);
    query.bindValue(":toid", r.toID);
    query.bindValue(":amount", r.amount);
    query.bindValue(":date", r.date);
    if(query.exec()) return true;
    qDebug() << "updateTransaction error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

bool DbManager::deleteCustomer(const Customer r) {
    QSqlQuery query(db);
    if(!existsRecordQuery("SELECT * FROM Customer where id=:id", r.id)) return false;
    query.prepare("DELETE from Customer where id=:id");
    query.bindValue(":id", r.id);
    if(query.exec()) return true;
    qDebug() << "deleteCustomer error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

bool DbManager::deleteAccount(const Account r) {
    QSqlQuery query(db);
    if(!existsRecordQuery("SELECT * FROM Account where id=:id", r.id)) return false;
    query.prepare("DELETE from Account where id=:id");
    query.bindValue(":id", r.id);
    if(query.exec()) return true;
    qDebug() << "deleteAccount error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

bool DbManager::deleteTransaction(const Transaction r) {
    QSqlQuery query(db);
    if(!existsRecordQuery("SELECT * FROM Transaction where id=:id", r.id)) return false;
    query.prepare("DELETE from Transaction where id=:id");
    query.bindValue(":id", r.id);
    if(query.exec()) return true;
    qDebug() << "deleteTransaction error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}

Customer DbManager::fetchCustomer(const Customer r) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer WHERE id=:id");
    query.bindValue(":id", r.id);
    Customer getC;
    if(query.exec()) {
        if(!query.next() && !query.first()) return getC;
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

Account DbManager::fetchAccount(const Account r) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account WHERE id=:id");
    query.bindValue(":id", r.id);
    Account getR;
    if(query.exec()) {
        if(!query.next() && !query.first()) return getR;
        QSqlRecord record = query.record();
        getR.id = record.value("id").toString();
        getR.name = record.value("name").toString();
        getR.customerID = query.value("customerid").toString();
        getR.balance = query.value("balance").toString();
    } else {
        qDebug() << "fetchAccount error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return getR;
}

Transaction DbManager::fetchTransaction(const Transaction r) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Transaction WHERE id=:id");
    query.bindValue(":id", r.id);
    Transaction getC;
    if(query.exec()) {
        if(!query.next() && !query.first()) return getC;
        QSqlRecord record = query.record();
        getC.id = record.value("id").toString();
        getC.fromID = record.value("fromid").toString();
        getC.toID = query.value("toid").toString();
        getC.amount = query.value("amount").toString();
        getC.date = query.value("date").toString();
    } else {
        qDebug() << "fetchTransaction error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return getC;
}

QSqlQueryModel* DbManager::fetchCustomerList() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer");
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchCustomerList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return model;
}

QSqlQueryModel* DbManager::fetchAccountList() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account");
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchAccountList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return model;
}

QSqlQueryModel* DbManager::fetchTransactionList() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Transaction");
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchTransactionList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return model;
}

bool DbManager::existsRecordQuery(const QString queryString, QString id) {
    QSqlQuery query(db);
    query.prepare(queryString);
    query.bindValue(":id", id);
    if(query.exec()) {
        if(query.isSelect() && query.next()) return true;
        else return false;
    }
    qDebug() << "existsQuery error: " << query.lastError();
    qDebug() << query.executedQuery();
    return false;
}
