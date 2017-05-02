#include "customerlist.h"
#include "ui_customerlist.h"
#include "customerdetails.h"
#include "dbmanager.h"

CustomerList::CustomerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerList)
{
    ui->setupUi(this);
    DbManager *dbManager = new DbManager();
    ui->CustList->setModel(dbManager->fetchCustomerList());



}

CustomerList::~CustomerList()
{
    delete ui;
}

void CustomerList::on_buttonBack_clicked()
{
    this->close();
    emit showPrev();
}


void CustomerList::on_buttonNewCustomer_clicked()
{
    hide();
    CustomerDetails *CusDetai = new CustomerDetails();
    QObject::connect(CusDetai, SIGNAL(showPrev()), SLOT(show()));
    CusDetai->show();
}


void CustomerList::on_loadcust_clicked()
{

}
