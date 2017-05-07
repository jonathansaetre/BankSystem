#include <accountcreate.h>
#include <ui_accountcreate.h>
#include <c.cpp>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlRecord>


AccountCreate::AccountCreate(QWidget *parent) : QDialog(parent), ui(new Ui::accountcreate) {
    ui->setupUi(this);
    model = DbManager::getInstance()->fetchCustomerList();
    ui->comboAccount->setModel(model);
    ui->comboAccount->setModelColumn(C::DB_ACCOUNT_ACCOUNTNR);
}

AccountCreate::~AccountCreate() {
    delete ui;
}

void AccountCreate::on_closeButton_clicked() {
    close();
    emit showPrev();
}



void AccountCreate::on_comboAccount_currentIndexChanged() {
    int index = ui->comboAccount->currentIndex();
    QString name = model->record(index).value(C::DB_ACCOUNT_NAME).toString();
    ui->nameBox->setText(name);
}

void AccountCreate::on_addButton_clicked() {
    Account ac;
    ac.customerID = ui->comboAccount->currentText();
    ac.accountnr = ui->accounNrBox->text();
    ac.name = ui->nameBox->text();
    ac.balance = ui->balanceBox->text();
    ac.date = ui->dateBox->text();

    if(DbManager::getInstance()->addAccount(ac)) {
        QMessageBox::information(this, "Add Account", "Added account successfully");
    } else {
        QMessageBox::information(this, "Add customer", "Add account failed");
    }

    //Initialise
    model = DbManager::getInstance()->fetchCustomerList();
    ui->comboAccount->setModel(model);
    ui->comboAccount->setModelColumn(C::DB_ACCOUNT_ACCOUNTNR);
    ui->accounNrBox->setText("");
    ui->nameBox->setText("");
    ui->balanceBox->setText("");
    ui->dateBox->setText("");
}
