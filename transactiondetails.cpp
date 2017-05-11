#include <transactiondetails.h>
#include <ui_transactiondetails.h>
#include <transactionlist.h>

TransactionDetails::TransactionDetails(QWidget *parent) : QWidget(parent), ui(new Ui::TransactionDetails) {
    ui->setupUi(this);
}

TransactionDetails::~TransactionDetails() {
    delete ui;
}

void TransactionDetails::init(Customer customer) {
    this->customer = customer;

}

void TransactionDetails::on_buttonLagre_clicked() {

}

void TransactionDetails::on_buttonBack_clicked() {
    close();
    emit showPrev();
}
