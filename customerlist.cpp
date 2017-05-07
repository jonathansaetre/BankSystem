#include <customerlist.h>
#include <ui_customerlist.h>
#include <customerdetails.h>
#include <dbmanager.h>


CustomerList::CustomerList(QWidget *parent) : QWidget(parent), ui(new Ui::CustomerList) {
    ui->setupUi(this);
    model = new QSqlQueryModel();
    ui->custList->setModel(model);
    model->setQuery(DbManager::getInstance()->fetchCustomerFTSlist(QString("")));
    QObject::connect(ui->textSearchEdit, SIGNAL(textChanged(QString)), this, SLOT(textSeachEditChanged(QString)));
    QObject::connect(ui->custList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(custListDoubleClicked(QModelIndex)));
}

CustomerList::~CustomerList() {
    delete ui;
}

void CustomerList::on_buttonBack_clicked() {
    this->close();
    emit showPrev();
}

void CustomerList::on_buttonNewCustomer_clicked() {
    hide();
    CustomerDetails *custDetail = new CustomerDetails();
    custDetail->newCustomer();
    QObject::connect(custDetail, SIGNAL(showPrev()), SLOT(show()));
    custDetail->show();
}

void CustomerList::textSeachEditChanged(QString text) {
    model->setQuery(DbManager::getInstance()->fetchCustomerFTSlist(text));
}

void CustomerList::custListDoubleClicked(QModelIndex index) {
    hide();
    CustomerDetails *custDetail = new CustomerDetails();
    custDetail->editCustomer(model, index.row());
    QObject::connect(custDetail, SIGNAL(showPrev()), SLOT(showCustList()));
    custDetail->show();
}

void CustomerList::showCustList() {
    model->setQuery(DbManager::getInstance()->fetchCustomerFTSlist(""));
    show();
}
