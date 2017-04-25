#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerlist.h"
#include "Transactionlist.h"

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
}
