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
        error("addCustomer", query);
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
        error("addCustomerFST", query);
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
        error("addAccount", query);
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
        error("addTransaction", query);
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
    query.prepare("UPDATE Customer SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email, state=:state WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    query.bindValue(":state", r.state);
    db.transaction();
    bool success = query.exec();
    if(success) {
        success = updateCustomerFST(r);
    } else {
        error("updateCustomer", query);
    }
    if(success) db.commit();
    else db.rollback();
    return success;
}

bool DbManager::updateCustomerFST(const Customer r) {
    QSqlQuery query(db);
    query.prepare("UPDATE CustomerFTS SET name=:name, ssn=:ssn, phone=:phone, address=:address, email=:email, state=:state WHERE id MATCH :id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.ssn);
    query.bindValue(":phone", r.phone);
    query.bindValue(":address", r.address);
    query.bindValue(":email", r.email);
    query.bindValue(":state", r.state);
    bool success = query.exec();
    if(!success) {
        error("updateCustomerFST", query);
    }
    return success;
}

bool DbManager::updateAccount(const Account r) {
    QSqlQuery query(db);
    query.prepare("UPDATE Account SET name=:name, customerid=:customerid, balance=:balance, state=:state WHERE id=:id");
    query.bindValue(":id", r.id);
    query.bindValue(":name", r.name);
    query.bindValue(":ssn", r.customerID);
    query.bindValue(":phone", r.balance);
    query.bindValue(":state", r.state);
    bool success = query.exec();
    if(!success) {
        error("updateAccount", query);
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
            cust.state = query.value(DB_CUSTOMER_STATE).toInt();
        } else {
            error("fetchCustomer error: Record not found.", query);
        }
    } else {
        error("fetchCustomer", query);
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
            account.state = query.value(DB_ACCOUNT_STATE).toInt();
        } else {
            error("fetchAccount error: Record not found.", query);
        }
    } else {
        error("fetchAccount", query);
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
            error("fetchTransaction error: Record not found.", query);
        }
    } else {
        error("fetchTransaction", query);
    }
    return trans;
}

QSqlQueryModel* DbManager::fetchCustomerList(int state) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Customer WHERE state=:state");
    query.bindValue(":state", state);
    if(query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "fetchCustomerList error: " << query.lastError();
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
    return model;
}

QSqlQuery DbManager::searchCustomer(QString searchText, int state) {
    QSqlQuery query(db);
    searchText = searchText.trimmed();
    QString s = "SELECT * FROM CustomerFTS WHERE state MATCH :state";
    if(searchText.isEmpty()){
        query.prepare(s);
    } else {
        searchText += "*";
        query.prepare(s + " AND CustomerFTS MATCH :searchText");
        query.bindValue(":searchText", searchText);
    }
    query.bindValue(":state", state);
    if(!query.exec()) {
        error("fetchCustomerFTSlist", query);
    }
    return query;
}

QSqlQueryModel* DbManager::fetchAccountList(QString customerID) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM Account where customerid=:customerid AND state=1");
    query.bindValue(":customerid", customerID);
    if(query.exec()) {
        model->setQuery(query);
    } else {
        error("fetchAccountList", query);
    }
    return model;
}

QSqlQueryModel* DbManager::fetchTransactionList(QString customerID) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(db);
    QString s = "SELECT * FROM Transaction";
    if(customerID.isEmpty()){
        query.prepare(s);
    } else {
        query.prepare(s + " WHERE customerid=:customerid");
        query.bindValue(":customerid", customerID);
    }
    if(query.exec()) {
        model->setQuery(query);
    } else {
        error("fetchTransactionList", query);
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
        error("existsQuery", query);
    }
    return finnes;
}

bool DbManager::runQuery(const QString queryString) {
    QSqlQuery query(db);
    query.prepare(queryString);
    bool success = true;
    if(!query.exec()) {
        error("runQuery", query);
        success = false;
    }
    return success;
}

void DbManager::error(QString s, QSqlQuery query) {
    qDebug() << s << " error: " << query.lastError();
    qDebug() << query.executedQuery();
    qDebug() << query.boundValues();
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
