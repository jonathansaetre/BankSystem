
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
    QString name;
    QString customerID;
    QString balance;
};

struct Transaction {
    QString id;
    QString fromID;
    QString toID;
    QString amount;
    QString date;
};
