#include <customerdetails.h>
#include <ui_customerdetails.h>
#include <accountlist.h>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <transactionlist.h>

CustomerDetails::CustomerDetails(QWidget *parent) : QWidget(parent), ui(new Ui::CustomerDetails) {
    ui->setupUi(this);
    setFocus();
}

CustomerDetails::~CustomerDetails() {
    delete ui;
}

void CustomerDetails::newCustomer() {
    setWindowTitle("New customer");
    ui->labelTitle->setText("New customer");
    ui->accountButton->hide();
    ui->transactionButton->hide();
}

void CustomerDetails::editCustomer(Customer customer) {
    setWindowTitle("Edit customer");
    ui->labelTitle->setText("Edit customer");
    this->customer = customer;
    ui->nameBox->setText(customer.name);
    ui->ssnBox->setText(customer.ssn);
    ui->phoneBox->setText(customer.phone);
    ui->addressBox->setText(customer.address);
    ui->emailBox->setText(customer.email);
}

void CustomerDetails::save(bool closeWindow) {
    if(ui->nameBox->text().isEmpty() || ui->ssnBox->text().isEmpty()) {
        QMessageBox::information(this, "New customer", "Missing name or ssn.");
    } else if(ui->addressBox->text().isEmpty() && ui->phoneBox->text().isEmpty() && ui->emailBox->text().isEmpty()) {
        QMessageBox::information(this, "New customer", "It's required with at least one way of contact: Phone, address or email.");
    }
    bool success;
    if(customer.id.isEmpty()) {
        Customer cust = DbManager::getInstance()->addCustomer(getRecord());
        if(!cust.id.isEmpty()){
            success = true;
            customer = cust;
            ui->accountButton->show();
            ui->transactionButton->show();
        }
    } else success = DbManager::getInstance()->updateCustomer(getRecord());
    if(!success) {
        QString action = customer.id.isEmpty() ? "Add" : "Update";
        QMessageBox::information(this, action + " ", action + " customer failed");
    }
}

Customer CustomerDetails::getRecord() {
    Customer c;
    c.id = customer.id;
    c.name = ui->nameBox->text();
    c.ssn = ui->ssnBox->text();
    c.phone = ui->phoneBox->text();
    c.address = ui->addressBox->text();
    c.email = ui->emailBox->text();
    return c;
}

void CustomerDetails::on_buttonCancel_clicked() {
    close();
    emit showPrev();
}

void CustomerDetails::on_buttonSave_clicked() {
    save(true);
}

void CustomerDetails::on_accountButton_clicked()
{    
    hide();
    AccountList *accountlist = new AccountList();
    accountlist->init(customer);
    QObject::connect(accountlist, SIGNAL(showPrev()), SLOT(showCustDetails()));
    accountlist->show();
}

void CustomerDetails::showCustDetails() {
    show();
}

void CustomerDetails::on_transactionButton_clicked() {
    hide();
    TransactionList *transactionlist = new TransactionList();
    transactionlist->init(customer);
    QObject::connect(transactionlist, SIGNAL(showPrev()), SLOT(show()));
    transactionlist->show();
}
