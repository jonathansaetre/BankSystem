#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <customerlist.h>
#include <transactionlist.h>
#include <customerdetails.h>
#include <transactiondetails.h>
#include <dbmanager.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    DbManager::close();
    delete ui;
}

void MainWindow::on_buttonCustomers_clicked() {
    hide();
    CustomerList *customerList = new CustomerList();
    QObject::connect(customerList, SIGNAL(showPrev()), SLOT(show()));
    customerList->show();
}

void MainWindow::on_buttonTransactions_clicked() {
    hide();
    TransactionList *transactionlist = new TransactionList();
    transactionlist->init();
    QObject::connect(transactionlist, SIGNAL(showPrev()), SLOT(show()));
    transactionlist->show();
}

void MainWindow::on_exitButton_clicked() {
    DbManager::close();
    QApplication::quit();
}
