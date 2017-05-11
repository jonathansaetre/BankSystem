#include <dbmanager.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QSqlRecord>
#include <QFileInfo>
#include <QMessageBox>
#include <c.cpp>

DbManager* DbManager::instance = NULL;
DbManager* DbManager::getInstance() {
    if(instance == NULL || !instance->db.isOpen()) instance = new DbManager();
    return instance;
}

void DbManager::close() {
    if(instance != NULL && instance->db.isOpen()) {
        instance->db.close();
    }
}

DbManager::DbManager() {
    QFileInfo check_file("BankingSystem.db");
    if (!(check_file.exists() && check_file.isFile())) {
        QMessageBox::critical(NULL, "Connecting to database", "Couldn't locate the database");
        qDebug() << "Error DbManager: Couldn't locate the database";
        return;
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("BankingSystem.db");
    if (!db.open()) {
        QMessageBox::critical(NULL, "Connecting to database", "Failed connecting to database");
        qDebug() << "Error DbManager: Failed connecting to database";
        return;
    }
    if(db.tables().isEmpty() || !db.tables().contains("Customer") || !db.tables().contains("Account") || !db.tables().contains("Transaction") || !db.tables().contains("CustomerFTS")) {
        db.close();
        QMessageBox::critical(NULL, "Connecting to database", "Database is not configured correctly");
        qDebug() << "Error DbManager: Database is not configured correctly";
    }
    qDebug() << "DbManager created";
}

bool DbManager::addCustomer(const Customer r) {
    bool exists = existsQuery("SELECT id FROM Customer where id = '" + r.id + "'");
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Customer (name, ssn, phone, address, email) VALUES (:name, :ssn, :phone, :address, :email)");
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    bool success = query.exec();
    db.commit();
    if(success) {
        Customer r2 = r;
        r2.id = query.lastInsertId().toString();
        addCustomerFST(r2);
    } else {
        qDebug() << query.executedQuery();
        qDebug() << "Error addCustomer:  " << query.lastError();
    }
    return success;
}

bool DbManager::addCustomerFST(const Customer r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO CustomerFTS (id, name, ssn, phone, address, email) VALUES (:id, :name, :ssn, :phone, :address, :email)");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error addCustomerFST:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::addAccount(const Account r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Account (customerid, accountnr, name, balance, date) VALUES (:customerid, :accountnr, :name, :balance, :date)");
    query.bindValue(":customerid", r.customerID);
    query.bindValue(":accountnr", r.accountnr);
    query.bindValue(":name", r.name);
    query.bindValue(":balance", r.balance);
    query.bindValue(":date", r.date);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error addAccount:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::addTransaction(const Transaction r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("INSERT INTO Transaction (fromid, toid, amount, date) VALUES (:fromid, :toid, :amount, :date)");
    query.bindValue(":fromid", r.fromID);
    query.bindValue(":toid", r.toID);
    query.bindValue(":amount", r.amount);
    query.bindValue(":date", r.date);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error addTransaction:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::updateCustomer(const Customer r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("UPDATE Customer SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    bool success = query.exec();
    db.commit();
    if(success) {
        updateCustomerFST(r);
    } else {
        qDebug() << "Error updateCustomer: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    return success;
}

bool DbManager::updateCustomerFST(const Customer r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("UPDATE CustomerFTS SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email WHERE id MATCH :id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error updateCustomerFST:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::updateAccount(const Account r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("UPDATE Account SET name=:name, customerid=:customerid, balance=:balance WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.customerID);
    query.bindValue(":phone", r.balance);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error updateAccount:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::updateTransaction(const Transaction r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("UPDATE Transaction SET fromid=:fromid, toid=:toid, amount=:amount, date=:date WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":fromid", r.fromID);
    query.bindValue(":toid", r.toID);
    query.bindValue(":amount", r.amount);
    query.bindValue(":date", r.date);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error updateTransaction:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::deleteCustomer(const Customer r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("DELETE from Customer where id=:id");
    query.bindValue(":id", r.id);
    bool success = query.exec();
    if(success) {
        deleteCustomerFST(r);
    } else {
        qDebug() << query.executedQuery();
        qDebug() << "Error deleteCustomer:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::deleteCustomerFST(const Customer r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("DELETE from CustomerFTS where id MATCH :id");
    query.bindValue(":id", r.id);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error deleteCustomerFST:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::deleteAccount(const Account r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("DELETE from Account where id=:id");
    query.bindValue(":id", r.id);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error deleteAccount:  " << query.lastError();
    }
    db.commit();
    return success;
}

bool DbManager::deleteTransaction(const Transaction r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("DELETE from Transaction where id=:id");
    query.bindValue(":id", r.id);
    bool success = query.exec();
    if(!success) {
        qDebug() << query.executedQuery();
        qDebug() << "Error deleteTransaction:  " << query.lastError();
    }
    db.commit();
    return success;
}

Customer DbManager::fetchCustomer(const Customer r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer WHERE id=:id");
    query.bindValue(":id", r.id);
    Customer getC;
    if(query.exec()) {
        if(!query.next() && !query.first()) return getC;
        QSqlRecord record = query.record();
        getC.id = record.value(C::DB_CUSTOMER_ID).toString();
        getC.name = record.value(C::DB_CUSTOMER_NAME).toString();
        getC.ssn = query.value(C::DB_CUSTOMER_SSN).toString();
        getC.phone = query.value(C::DB_CUSTOMER_PHONE).toString();
        getC.address = query.value(C::DB_CUSTOMER_ADDRESS).toString();
        getC.email = query.value(C::DB_CUSTOMER_EMAIL).toString();
    } else {
        qDebug() << "fetchCustomer error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return getC;
}

Account DbManager::fetchAccount(const Account r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account WHERE id=:id");
    query.bindValue(":id", r.id);
    Account getR;
    if(query.exec()) {
        if(query.first()) {
            QSqlRecord record = query.record();
            getR.id = record.value(C::DB_ACCOUNT_ID).toString();
            getR.name = record.value(C::DB_ACCOUNT_NAME).toString();
            getR.customerID = query.value(C::DB_ACCOUNT_CUSTOMERID).toString();
            getR.balance = query.value(C::DB_ACCOUNT_BALANCE).toString();
            getR.accountnr = query.value(C::DB_ACCOUNT_ACCOUNTNR).toString();
            getR.date = query.value(C::DB_ACCOUNT_DATE).toString();
        }
    } else {
        qDebug() << "fetchAccount error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return getR;
}

Transaction DbManager::fetchTransaction(const Transaction r) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Transaction WHERE id=:id");
    query.bindValue(":id", r.id);
    Transaction getR;
    if(query.exec()) {
        if(query.first()) {
            QSqlRecord record = query.record();
            getR.id = record.value(C::DB_TRANSACTION_ID).toString();
            getR.fromID = record.value(C::DB_TRANSACTION_FROMID).toString();
            getR.toID = query.value(C::DB_TRANSACTION_TOID).toString();
            getR.amount = query.value(C::DB_TRANSACTION_AMOUNT).toString();
            getR.date = query.value(C::DB_TRANSACTION_DATE).toString();
        }
    } else {
        qDebug() << "fetchTransaction error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return getR;
}

QSqlQueryModel* DbManager::fetchCustomerList() {
    db.transaction();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer");
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchCustomerList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return model;
}

QSqlQuery DbManager::fetchCustomerFTSlist(QString s) {
    db.transaction();
    QSqlQuery query(db);
    s = s.trimmed();
    if(s.isEmpty()) query.prepare("SELECT * FROM CustomerFTS");
    else {
        s += "*";
        query.prepare("SELECT * FROM CustomerFTS WHERE CustomerFTS MATCH :s");
        query.bindValue(":s", s);
    }
    if(!query.exec()) {
        qDebug() << "fetchCustomerList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return query;
}

QSqlQueryModel* DbManager::fetchAccountList(QString customerID) {
    db.transaction();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account where customerid=:customerid");
    query.bindValue(":customerid", customerID);
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchAccountList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return model;
}

QSqlQueryModel* DbManager::fetchTransactionList(QString customerID) {
    db.transaction();
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Transaction where customerid=:customerid");
    query.bindValue(":customerid", customerID);
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchTransactionList error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return model;
}

bool DbManager::existsSSN(QString ssn) {
    return existsQuery("SELECT ssn FROM Customer where ssn = '" + ssn + "'");
}

bool DbManager::existsQuery(const QString queryString) {
    db.transaction();
    QSqlQuery query(db);
    query.prepare(queryString);
    bool finnes;
    if(query.exec()) {
        if(query.isSelect() && query.first()) finnes = true;
    } else {
        qDebug() << "existsQuery error: " << query.lastError();
        qDebug() << query.executedQuery();
    }
    db.commit();
    return finnes;
}
