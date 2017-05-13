#include <accountcreate.h>
#include <ui_accountcreate.h>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlRecord>


AccountDetails::AccountDetails(QWidget *parent) : QDialog(parent), ui(new Ui::accountcreate) {
    ui->setupUi(this);
    setFocus();
    model = DbManager::getInstance()->fetchCustomerList();
    ui->comboAccount->setModel(model);
    ui->comboAccount->setModelColumn(DB_CUSTOMER_SSN);
}

AccountDetails::~AccountDetails() {
    delete ui;
}




void AccountDetails::on_comboAccount_currentIndexChanged() {
    int index = ui->comboAccount->currentIndex();
    QString name = model->record(index).value(DB_CUSTOMER_NAME).toString();
    ui->nameBox->setText(name);
}

void AccountDetails::on_saveButton_clicked() {
    Account ac;
    ac.customerID = ui->comboAccount->currentText();
    ac.accountnr = ui->accounNrBox->text();
    ac.name = ui->accountNameBox->text();
    ac.balance = ui->balanceBox->text().toInt();

    if(DbManager::getInstance()->addAccount(ac)) {
        QMessageBox::information(this, "Add Account", "Added account successfully");
    } else {
        QMessageBox::information(this, "Add customer", "Add account failed");
    }

    //Initialise
    model = DbManager::getInstance()->fetchCustomerList();
    ui->comboAccount->setModel(model);
    ui->comboAccount->setModelColumn(DB_CUSTOMER_SSN);
    ui->accounNrBox->setText("");
    ui->accountNameBox->setText("");
    ui->balanceBox->setText("");
    ui->dateBox->setText("");
}

void AccountDetails::on_closeButton_clicked()
{
    close();
    emit showPrev();
}

