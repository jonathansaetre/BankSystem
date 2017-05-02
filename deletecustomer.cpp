#include "deletecustomer.h"
#include "ui_deletecustomer.h"
#include "dbmanager.h"
#include<QSqlQueryModel>
#include <QSqlRecord>

Deletecustomer::Deletecustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deletecustomer)
{
    ui->setupUi(this);
    DbManager *dbmanager=new DbManager();
    model = dbmanager->fetchCustomerList();

    ui->combocustomer->setModel(model);
     ui->combocustomer->setModelColumn(2);
}

Deletecustomer::~Deletecustomer()
{
    delete ui;
}

void Deletecustomer::on_closeButton_clicked()
{
    close();
    emit showPrev();
}

void Deletecustomer::on_combocustomer_currentIndexChanged(const QString &arg1)
{
    int index=ui->combocustomer->currentIndex();

    QString ssn = model->record(index).value(1).toString();
    ui->name=ssn;
}

void Deletecustomer::on_deleteButton_clicked()
{
    DbManager db=new DbManager();
   // db.deleteCustomer()

}
