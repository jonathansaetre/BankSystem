#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerlist.h"
#include "transactionlist.h"
#include "customerdetails.h"
#include "deletecustomer.h"
#include "accountcreate.h"
#include <dbmanager.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonCustomers_clicked()
{
    hide();
    CustomerList *customerList = new CustomerList();
    QObject::connect(customerList, SIGNAL(showPrev()), SLOT(show()));
    customerList->show();
}

void MainWindow::on_buttonTransactions_clicked()
{
    hide();
    TransactionList *transactionlist = new TransactionList();
    QObject::connect(transactionlist, SIGNAL(showPrev()), SLOT(show()));
    transactionlist->show();

    Customer p;
    p.name = "Hans";
    p.ssn = "asdasd";
    p.phone = "sdsd";
    p.address = "ssssss";
    p.email = "sd";
    DbManager *db = new DbManager();
//    db->addCustomer(p);
}


void MainWindow::on_actionNew_triggered()
{
    hide();
    CustomerDetails *customerDet = new CustomerDetails();
    QObject::connect(customerDet, SIGNAL(showPrev()), SLOT(show()));
    customerDet->show();


}

void MainWindow::on_actionDelete_triggered()
{
    hide();
    Customerdelete *customerDelete = new Customerdelete();
    QObject::connect(customerDelete, SIGNAL(showPrev()), SLOT(show()));
    customerDelete->show();
}

void MainWindow::on_actionNew_2_triggered()
{
    hide();
   accountcreate *createaccount = new accountcreate();
    QObject::connect(createaccount, SIGNAL(showPrev()), SLOT(show()));
    createaccount->show();
}
