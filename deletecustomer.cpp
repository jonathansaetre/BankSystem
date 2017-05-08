#include <deletecustomer.h>
#include <ui_deletecustomer.h>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <c.cpp>

Customerdelete::Customerdelete(QWidget *parent) : QDialog(parent), ui(new Ui::Deletecustomer) {
    ui->setupUi(this);
    setFocus();
    model = DbManager::getInstance()->fetchCustomerList();
    ui->customerCombobox->setModel(model);
    ui->customerCombobox->setModelColumn(C::DB_CUSTOMER_SSN);
}

Customerdelete::~Customerdelete() {
    delete ui;
}

void Customerdelete::on_closeButton_clicked() {
    close();
    emit showPrev();
}

void Customerdelete::on_deleteButton_clicked() {
    Customer c;
    int index = ui->customerCombobox->currentIndex();
    c.id = model->record(index).value(C::DB_CUSTOMER_ID).toString();
    if(DbManager::getInstance()->deleteCustomer(c)){
        QMessageBox::information(this, "Delete customer ", "Deleted customer Successfully");
    } else {
        QMessageBox::information(this, "Delete customer ", "Deleted customer Failed");
    }

    model = DbManager::getInstance()->fetchCustomerList();
    ui->customerCombobox->setModel(model);
    ui->customerCombobox->setModelColumn(C::DB_CUSTOMER_SSN);
}

void Customerdelete::on_customerCombobox_currentIndexChanged() {
    int index = ui->customerCombobox->currentIndex();
    QString name = model->record(index).value(C::DB_CUSTOMER_NAME).toString();
    ui->nameBox->setText(name);
}
