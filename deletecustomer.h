#ifndef DELETECUSTOMER_H
#define DELETECUSTOMER_H
#include <QSqlQueryModel>
#include <dbmanager.h>
#include <QDialog>

namespace Ui {
class Deletecustomer;
}

class Customerdelete : public QDialog
{
    Q_OBJECT

public:
    explicit Customerdelete(QWidget *parent = 0);
    ~Customerdelete();



private slots:
    void on_closeButton_clicked();
    void on_deleteButton_clicked();


    void on_customersnn_editingFinished();

signals:
    void showPrev();

private:
    Ui::Deletecustomer *ui;
    QSqlQueryModel *model;
    Customer c;
    Customer getRecord();
};

#endif // DELETECUSTOMER_H
