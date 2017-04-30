#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerlist.h"
#include "transactionlist.h"
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

