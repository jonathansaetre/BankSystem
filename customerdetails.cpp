#include "customerdetails.h"
#include "ui_customerdetails.h"
#include "dbmanager.h"

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
    c.name=ui->name->text();
    c.ssn=ui->ssn->text();
    c.address=ui->address->text();
    c.phone=ui->phone->text();
   DbManager *db=new DbManager();
   db->addCustomer(c);

}
