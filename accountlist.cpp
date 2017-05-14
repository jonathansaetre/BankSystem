#include "accountlist.h"
#include "ui_accountlist.h"
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
    if(ui->leAccName->text().isEmpty() || ui->leBalance->text().isEmpty() || !Util::isNumber(ui->leBalance->text())) {
        QMessageBox::information(this, "Account", "You miss name or start balance.");
        return;
    }
    Account account;
    account.customerID = customer.id;
    account.name = ui->leAccName->text();
    account.balance = ui->leBalance->text().toInt();
    bool success = DbManager::getInstance()->addAccount(account);
    if(success) {
        ui->accountList->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    } else {
        QString action = customer.id.isEmpty() ? "Add" : "Update";
        QMessageBox::information(this, "Account", action + " account failed");
    }
}

void AccountList::on_backButton_clicked() {
    close();
    emit showPrev();
}
