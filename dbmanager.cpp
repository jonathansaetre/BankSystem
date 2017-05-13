#include <dbmanager.h>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QSqlRecord>
#include <QFileInfo>
#include <QMessageBox>
#include <QDate>

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
    if(db.tables().isEmpty() || !db.tables().contains("Customer") || !db.tables().contains("Account")
            || !db.tables().contains("Transaction") || !db.tables().contains("CustomerFTS") || !runQuery("PRAGMA foreign_keys = ON;")) {
        db.close();
        QMessageBox::critical(NULL, "Connecting to database", "Database is not configured correctly");
        qDebug() << "Error DbManager: Database is not configured correctly";
    }
    qDebug() << "DbManager created";
}

Customer DbManager::addCustomer(Customer cust) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Customer (name, ssn, phone, address, email) VALUES (:name, :ssn, :phone, :address, :email)");
    query.bindValue(":name", cust.name);
    query.bindValue(":ssn", cust.ssn);
    query.bindValue(":phone", cust.phone);
    query.bindValue(":address", cust.address);
    query.bindValue(":email", cust.email);
    db.transaction();
    bool success = query.exec();
    if(success) {
        cust.id = query.lastInsertId().toString();
        success = addCustomerFST(cust);
    } else {
        qDebug() << "Error addCustomer:  " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    if(!success) {
        cust.id = "";
        db.rollback();
    }
    db.commit();
    return cust;
}

bool DbManager::addCustomerFST(const Customer r) {
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
        qDebug() << "Error addCustomerFST:  " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return success;
}

bool DbManager::addAccount(const Account r) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Account (customerid, accountnr, name, balance) VALUES (:customerid, :accountnr, :name, :balance)");
    query.bindValue(":customerid", r.customerID);
    query.bindValue(":accountnr", getAccountnr());
    query.bindValue(":name", r.name);
    query.bindValue(":balance", r.balance);
    bool success = query.exec();
    if(!success) {
        qDebug() << "Error addAccount:  " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return success;
}

QString DbManager::getAccountnr() {
    int accountnr;
    do {
        accountnr = rand() % 100000000 + 100000000;
    } while(existsAccountNr(QString::number(accountnr)));
    return QString::number(accountnr);
}

bool DbManager::addTransaction(const Transaction r) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Transaction (fromid, toid, amount, date) VALUES (:fromid, :toid, :amount, :date)");
    query.bindValue(":fromid", r.fromAccountID);
    query.bindValue(":toid", r.toAccountID);
    query.bindValue(":amount", r.amount);
    query.bindValue(":date", r.date);
    db.transaction();
    bool success = query.exec();
    if(success) {
        Transaction r2 = r;
        r2.id = query.lastInsertId().toString();
        success = executeTransfer(r2);
    } else {
        qDebug() << "Error addTransaction:  " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    if(!success) db.rollback();
    return success;
}

bool DbManager::executeTransfer(const Transaction r) {
    Account fromAccount = fetchAccount(r.fromAccountID);
    fromAccount.balance -= r.amount;

    Account toAccount = fetchAccount(r.toAccountID);
    toAccount.balance += r.amount;

    return !fromAccount.id.isEmpty() && !toAccount.id.isEmpty() && updateAccount(fromAccount) && updateAccount(toAccount);
}



bool DbManager::updateCustomer(const Customer r) {
    QSqlQuery query(db);
    query.prepare("UPDATE Customer SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    db.transaction();
    bool success = query.exec();
    if(success) {
        success = updateCustomerFST(r);
    } else {
        qDebug() << "Error updateCustomer: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    if(success) db.commit();
    else db.rollback();
    return success;
}

bool DbManager::updateCustomerFST(const Customer r) {
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
        qDebug() << "Error updateCustomerFST:  " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return success;
}

bool DbManager::updateAccount(const Account r) {
    QSqlQuery query(db);
    query.prepare("UPDATE Account SET name=:name, customerid=:customerid, balance=:balance WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.customerID);
    query.bindValue(":phone", r.balance);
    bool success = query.exec();
    if(!success) {
        qDebug() << "Error updateAccount:  " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return success;
}

Customer DbManager::fetchCustomer(QString id) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer WHERE id=:id");
    query.bindValue(":id", id);
    Customer cust;
    if(query.exec()) {
        if(query.first()) {
            QSqlRecord record = query.record();
            cust.id = record.value(DB_CUSTOMER_ID).toString();
            cust.name = record.value(DB_CUSTOMER_NAME).toString();
            cust.ssn = query.value(DB_CUSTOMER_SSN).toString();
            cust.phone = query.value(DB_CUSTOMER_PHONE).toString();
            cust.address = query.value(DB_CUSTOMER_ADDRESS).toString();
            cust.email = query.value(DB_CUSTOMER_EMAIL).toString();
        } else {
            qDebug() << "fetchCustomer error: " << "Record not found.";
            qDebug() << query.executedQuery();
            qDebug() << query.boundValues();
        }
    } else {
        qDebug() << "fetchCustomer error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return cust;
}

Account DbManager::fetchAccount(QString id) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account WHERE id=:id");
    query.bindValue(":id", id);
    Account account;
    if(query.exec()) {
        if(query.first()) {
            QSqlRecord record = query.record();
            account.id = record.value(DB_ACCOUNT_ID).toString();
            account.name = record.value(DB_ACCOUNT_NAME).toString();
            account.customerID = query.value(DB_ACCOUNT_CUSTOMERID).toString();
            account.balance = query.value(DB_ACCOUNT_BALANCE).toInt();
            account.accountnr = query.value(DB_ACCOUNT_ACCOUNTNR).toString();
        } else {
            qDebug() << "fetchAccount error: " << "Record not found.";
            qDebug() << query.executedQuery();
            qDebug() << query.boundValues();
        }
    } else {
        qDebug() << "fetchAccount error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return account;
}

Transaction DbManager::fetchTransaction(QString id) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Transaction WHERE id=:id");
    query.bindValue(":id", id);
    Transaction trans;
    if(query.exec()) {
        if(query.first()) {
            QSqlRecord record = query.record();
            trans.id = record.value(DB_TRANSACTION_ID).toString();
            trans.fromAccountID = record.value(DB_TRANSACTION_FROMACCOUNTID).toString();
            trans.toAccountID = query.value(DB_TRANSACTION_TOACCOUNTID).toString();
            trans.amount = query.value(DB_TRANSACTION_AMOUNT).toInt();
            trans.date = QDate::fromString(query.value(DB_TRANSACTION_DATE).toString(), "ddMMyyyy");
        } else {
            qDebug() << "fetchTransaction error: " << "Record not found.";
            qDebug() << query.executedQuery();
            qDebug() << query.boundValues();
        }
    } else {
        qDebug() << "fetchTransaction error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return trans;
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
        qDebug() << query.boundValues();
    }
    return model;
}

QSqlQuery DbManager::fetchCustomerFTSlist(QString s) {
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
        qDebug() << query.boundValues();
    }
    return query;
}

QSqlQueryModel* DbManager::fetchAccountList(QString customerID) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account where customerid=:customerid");
    query.bindValue(":customerid", customerID);
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchAccountList error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return model;
}

QSqlQueryModel* DbManager::fetchTransactionList(QString customerID) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    QString s = "SELECT * FROM Transaction";
    if(!customerID.isEmpty()) s += " where customerid=:customerid";
    query.prepare(s);
    if(!customerID.isEmpty()) query.bindValue(":customerid", customerID);
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchTransactionList error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return model;
}

bool DbManager::existsSSN(QString ssn) {
    return existsQuery("SELECT ssn FROM Customer where ssn = '" + ssn + "'");
}

bool DbManager::existsAccountNr(QString accountNr) {
    return existsQuery("SELECT accountnr FROM Account where accountnr = '" + accountNr + "'");
}

bool DbManager::existsQuery(const QString queryString) {
    QSqlQuery query(db);
    query.prepare(queryString);
    bool finnes;
    if(query.exec()) {
        if(query.isSelect() && query.first()) finnes = true;
    } else {
        qDebug() << "existsQuery error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return finnes;
}

bool DbManager::runQuery(const QString queryString) {
    QSqlQuery query(db);
    query.prepare(queryString);
    bool success = true;
    if(!query.exec()) {
        qDebug() << "runQuery error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
        success = false;
    }
    return success;
}

//QSqlRecord DbManager::selectQuery(const QString queryString) {
//    QSqlQuery query(db);
//    query.prepare(queryString);
//    bool success = true;
//    if(!query.exec() || !query.first() || !query.isSelect()) {
//        qDebug() << "getQuery error: " << query.lastError();
//        qDebug() << query.executedQuery();
//        return QSqlRecord();
//    }
//    return query.record();
//}
