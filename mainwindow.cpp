#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "customerlist.h"

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
    setCentralWidget(new CustomerList());
//    CustomerList *w = ;
//    w->show();
//    this->destroy();
}
