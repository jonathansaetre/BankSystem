#include <customerlist.h>
#include <ui_customerlist.h>
#include <customerdetails.h>


CustomerList::CustomerList(QWidget *parent) : QWidget(parent), ui(new Ui::CustomerList) {
    ui->setupUi(this);
    setFocus();
    model = DbManager::getInstance()->fetchQueryCustomerList();
    ui->custList->setModel(model);
    ui->custList->hideColumn(DB_CUSTOMER_ID);
    ui->custList->hideColumn(DB_CUSTOMER_STATE);
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

void CustomerList::textSeachEditChanged(QString searchText) {
    model->setQuery(DbManager::getInstance()->searchCustomer(searchText));
}

void CustomerList::custListDoubleClicked(QModelIndex index) {
    hide();
    CustomerDetails *custDetail = new CustomerDetails();
    custDetail->editCustomer(Util::getCustomer(model, index.row()));
    QObject::connect(custDetail, SIGNAL(showPrev()), SLOT(showCustList()));
    custDetail->show();
}

void CustomerList::showCustList() {
    model = DbManager::getInstance()->fetchQueryCustomerList();
    show();
}
