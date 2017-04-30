#ifndef DELETECUSTOMER_H
#define DELETECUSTOMER_H

#include <QDialog>

namespace Ui {
class Deletecustomer;
}

class Deletecustomer : public QDialog
{
    Q_OBJECT

public:
    explicit Deletecustomer(QWidget *parent = 0);
    ~Deletecustomer();

private:
    Ui::Deletecustomer *ui;
};

#endif // DELETECUSTOMER_H
