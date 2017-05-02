#include "deletecustomer.h"
#include "ui_deletecustomer.h"
#include <columnindexes.cpp>
#include<QSqlQueryModel>
#include<QMessageBox>
#include <QSqlRecord>

Customerdelete::Customerdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deletecustomer)
{
    ui->setupUi(this);
    dbmanager=new DbManager();
    model = dbmanager->fetchCustomerList();

    ui->customerCombobox->setModel(model);
    ui->customerCombobox->setModelColumn(CUSTOMER_SSN);
}

Customerdelete::~Customerdelete()
{
    delete ui;
}

void Customerdelete::on_closeButton_clicked()
{
    close();
    emit showPrev();
}



void Customerdelete::on_deleteButton_clicked()
{
    Customer c;
    int index = ui->customerCombobox->currentIndex();
    c.id = model->record(index).value(CUSTOMER_ID).toString();
    if(dbmanager->deleteCustomer(c)){
        QMessageBox::information(this,"Delete customer ","Deleted customer Successfully");
    }else{
        QMessageBox::information(this,"Delete customer ","Deleted customer Failed");
    }


}

void Customerdelete::on_customerCombobox_currentIndexChanged(const QString &arg1)
{

    int index = ui->customerCombobox->currentIndex();

    QString name = model->record(index).value(CUSTOMER_NAME).toString();
    ui->nameBox->setText(name);
}
