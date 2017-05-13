#include <QAbstractItemModel>
#include <QDate>

//Objects
struct Customer {
    QString id;
    QString name;
    QString ssn;
    QString address;
    QString phone;
    QString email;
    QString state;
};

struct Account {
    QString id;
    QString customerID;
    QString accountnr;
    QString name;
    int balance = 0;
    QString state;
};

struct Transaction {
    QString id;
    QString fromAccountID;
    QString toAccountID;
    int amount = 0;
    QDate date;
};

static const int DB_CUSTOMER_ID = 0;
static const int DB_CUSTOMER_NAME = 1;
static const int DB_CUSTOMER_SSN = 2;
static const int DB_CUSTOMER_ADDRESS = 3;
static const int DB_CUSTOMER_PHONE = 4;
static const int DB_CUSTOMER_EMAIL = 5;
static const int DB_CUSTOMER_STATE = 6;

static const int DB_ACCOUNT_ID = 0;
static const int DB_ACCOUNT_CUSTOMERID = 1;
static const int DB_ACCOUNT_ACCOUNTNR = 2;
static const int DB_ACCOUNT_NAME = 3;
static const int DB_ACCOUNT_BALANCE = 4;
static const int DB_ACCOUNT_STATE = 5;

static const int DB_TRANSACTION_ID = 0;
static const int DB_TRANSACTION_FROMACCOUNTID = 1;
static const int DB_TRANSACTION_TOACCOUNTID = 2;
static const int DB_TRANSACTION_AMOUNT = 3;
static const int DB_TRANSACTION_DATE = 4;

class Util {
public:
    static Customer getCustomer(QAbstractItemModel *model, int index) {
        Customer customer;
        customer.id = model->index(index, DB_CUSTOMER_ID).data().toString();
        customer.name = model->index(index, DB_CUSTOMER_NAME).data().toString();
        customer.ssn = model->index(index, DB_CUSTOMER_SSN).data().toString();
        customer.phone = model->index(index, DB_CUSTOMER_PHONE).data().toString();
        customer.address = model->index(index, DB_CUSTOMER_ADDRESS).data().toString();
        customer.email = model->index(index, DB_CUSTOMER_EMAIL).data().toString();
        customer.state = model->index(index, DB_CUSTOMER_STATE).data().toString();
        return customer;
    }

    static Account getAccount(QAbstractItemModel *model, int index) {
        Account account;
        account.id = model->index(index, DB_ACCOUNT_ID).data().toString();
        account.customerID = model->index(index, DB_ACCOUNT_CUSTOMERID).data().toString();
        account.accountnr = model->index(index, DB_ACCOUNT_ACCOUNTNR).data().toString();
        account.name = model->index(index, DB_ACCOUNT_NAME).data().toString();
        account.balance = model->index(index, DB_ACCOUNT_BALANCE).data().toInt();
        account.state = model->index(index, DB_ACCOUNT_STATE).data().toString();
        return account;
    }
};
