#include "objects.h"


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
    QString name;
    QString balance;
    QString address;
    QString phone;
    QString email;
};
