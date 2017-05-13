#include "accountlist.h"
#include "ui_accountlist.h"
#include <accountcreate.h>
#include <QSqlRecord>
#include <QMessageBox>

AccountList::AccountList(QWidget *parent) : QDialog(parent), ui(new Ui::AccountList)
{
    ui->setupUi(this);

}

AccountList::~AccountList() {
    delete ui;
}

void AccountList::init(Customer customer) {
    this->customer = customer;
    ui->accountList->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    ui->customerBox->setText(customer.name);
}

void AccountList::on_Newaccount_clicked() {
    Account account;
    account.customerID = customer.id;
    account.name = ui->leAccName->text();
    if(account.name.isEmpty()) return;
    bool success = DbManager::getInstance()->addAccount(account);
    if(success) {
        ui->accountList->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    } else {
        QString action = customer.id.isEmpty() ? "Add" : "Update";
        QMessageBox::information(this, action + " ", action + " customer failed");
    }
}

void AccountList::on_backButton_clicked() {
    close();
    emit showPrev();
}
