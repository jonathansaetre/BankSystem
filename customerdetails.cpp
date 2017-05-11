#include <customerdetails.h>
#include <ui_customerdetails.h>
#include <accountlist.h>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>

CustomerDetails::CustomerDetails(QWidget *parent) : QWidget(parent), ui(new Ui::CustomerDetails) {
    ui->setupUi(this);
    setFocus();
}

CustomerDetails::~CustomerDetails() {
    delete ui;
}

void CustomerDetails::newCustomer() {
    ui->labelTitle->setText("New customer");
}

void CustomerDetails::editCustomer(QSqlQueryModel *model, int index) {
    ui->labelTitle->setText("Edit customer");
    ui->buttonSave_New->hide();
    id = model->record(index).value(Util::DB_CUSTOMER_ID).toString();
    ui->nameBox->setText(model->record(index).value(Util::DB_CUSTOMER_NAME).toString());
    ui->ssnBox->setText(model->record(index).value(Util::DB_CUSTOMER_SSN).toString());
    ui->phoneBox->setText(model->record(index).value(Util::DB_CUSTOMER_ADDRESS).toString());
    ui->addressBox->setText(model->record(index).value(Util::DB_CUSTOMER_PHONE).toString());
    ui->emailBox->setText(model->record(index).value(Util::DB_CUSTOMER_EMAIL).toString());


}

void CustomerDetails::save(bool closeWindow) {
    bool success;
    if(id.isEmpty()) success = DbManager::getInstance()->addCustomer(getRecord());
    else success = DbManager::getInstance()->updateCustomer(getRecord());
    if(success) {
        if(closeWindow) {
            close();
            emit showPrev();
        } else {
            foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
                widget->clear();
            }
        }
    } else {
        QString action = id.isEmpty() ? "Add" : "Update";
        QMessageBox::information(this, action + " ", action + " customer failed");
    }
}

Customer CustomerDetails::getRecord() {
    Customer c;
    c.id = id;
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

void CustomerDetails::on_buttonSave_New_clicked() {
    save(false);
}



void CustomerDetails::on_accountButton_clicked()
{
    hide();
    AccountList *accountlist = new AccountList();
    accountlist->accounts(DbManager::getInstance()->fetchAccountList(ui->ssnBox->text()));
    accountlist->customerName(ui->nameBox->text());
    QObject::connect(accountlist, SIGNAL(showPrev()), SLOT(showCustDetails()));
    accountlist->show();
}

void CustomerDetails::showCustDetails() {
    show();
}

