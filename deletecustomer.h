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

private slots:
    void on_closeButton_clicked();

signals:
    void showPrev();

private:
    Ui::Deletecustomer *ui;
};

#endif // DELETECUSTOMER_H
