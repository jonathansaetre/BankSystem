#include "customerdetails.h"
#include "ui_customerdetails.h"
#include "dbmanager.h"
#include<QMessageBox>

CustomerDetails::CustomerDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerDetails)
{
    ui->setupUi(this);
}

CustomerDetails::~CustomerDetails()
{
    delete ui;
}

void CustomerDetails::on_CloseButton_clicked()
{
    close();
    emit showPrev();
}

void CustomerDetails::on_addButton_clicked()
{
    Customer c;
    c.name = ui->nameBox->text();
    c.ssn = ui->ssnBox->text();
    c.address = ui->addressBox->text();
    c.phone = ui->phoneBox->text();
    c.email = ui->emailBox->text();

   DbManager *db=new DbManager();

   if(db->addCustomer(c)){
         QMessageBox::information(this,"Add customer ","Added customer Successfully");
      }else{
         QMessageBox::information(this,"Add customer ","Added customer Failed");
     }


}
