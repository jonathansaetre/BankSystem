#include <customerdetails.h>
#include <ui_customerdetails.h>
#include <dbmanager.h>
#include <QMessageBox>

CustomerDetails::CustomerDetails(QWidget *parent) : QWidget(parent), ui(new Ui::CustomerDetails) {
    ui->setupUi(this);
}

CustomerDetails::~CustomerDetails() {
    delete ui;
}

void CustomerDetails::on_CloseButton_clicked() {
    close();
    emit showPrev();
}

void CustomerDetails::on_addButton_clicked() {
    Customer c;
    c.name = ui->nameBox->text();
    c.ssn = ui->ssnBox->text();
    c.address = ui->addressBox->text();
    c.phone = ui->phoneBox->text();
    c.email = ui->emailBox->text();

    if(DbManager::getInstance()->addCustomer(c)) {
        QMessageBox::information(this, "Add customer", "Added customer successfully");
    } else {
        QMessageBox::information(this, "Add customer", "Add customer failed");
    }
}
