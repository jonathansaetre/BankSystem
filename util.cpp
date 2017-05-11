#include <QAbstractItemModel>

struct Customer {
    QString id;
    QString name;
    QString ssn;
    QString address;
    QString phone;
    QString email;
};

struct Account {
    QString id;
    QString customerID;
    QString accountnr;
    QString name;
    QString balance;
    QString date;
};

struct Transaction {
    QString id;
    QString fromAccountID;
    QString fromAccountnr;
    QString toAccountID;
    QString toAccountnr;
    QString amount;
    QString date;
};

class Util {

public:
    static const int DB_CUSTOMER_ID = 0;
    static const int DB_CUSTOMER_NAME = 1;
    static const int DB_CUSTOMER_SSN = 2;
    static const int DB_CUSTOMER_ADDRESS = 3;
    static const int DB_CUSTOMER_PHONE = 4;
    static const int DB_CUSTOMER_EMAIL = 5;

    static const int DB_ACCOUNT_ID = 0;
    static const int DB_ACCOUNT_CUSTOMERID = 1;
    static const int DB_ACCOUNT_ACCOUNTNR = 2;
    static const int DB_ACCOUNT_NAME = 3;
    static const int DB_ACCOUNT_BALANCE = 4;
    static const int DB_ACCOUNT_DATE = 5;

    static const int DB_TRANSACTION_ID = 0;
    static const int DB_TRANSACTION_FROMID = 1;
    static const int DB_TRANSACTION_TOID = 2;
    static const int DB_TRANSACTION_AMOUNT = 3;
    static const int DB_TRANSACTION_DATE = 4;


    static Customer getCustomer(QAbstractItemModel *model, int index) {
        Customer c;
        c.id = model->index(index, DB_CUSTOMER_ID).data().toString();
        c.name = model->index(index, DB_CUSTOMER_NAME).data().toString();
        c.ssn = model->index(index, DB_CUSTOMER_SSN).data().toString();
        c.phone = model->index(index, DB_CUSTOMER_PHONE).data().toString();
        c.address = model->index(index, DB_CUSTOMER_ADDRESS).data().toString();
        c.email = model->index(index, DB_CUSTOMER_EMAIL).data().toString();
        return c;
    }


};
