#include <transactionlist.h>
#include <ui_transactionlist.h>
#include <transactiondetails.h>


TransactionList::TransactionList(QWidget *parent) : QWidget(parent), ui(new Ui::TransactionList) {
    ui->setupUi(this);
}

TransactionList::~TransactionList() {
    delete ui;
}

void TransactionList::init(Customer customer) {
    this->customer = customer;
    ui->listView->setModel(DbManager::getInstance()->fetchTransactionList(customer.id));
}

void TransactionList::on_buttonNewTransaction_clicked() {
    hide();
    TransactionDetails *transDet = new TransactionDetails();
    transDet->init(customer);
    QObject::connect(transDet, SIGNAL(showPrev()), SLOT(showTransactionList()));
    transDet->show();
}

void TransactionList::showTransactionList() {
    ui->listView->setModel(DbManager::getInstance()->fetchTransactionList(customer.id));
    show();
}

void TransactionList::on_buttonBack_clicked() {
    close();
    emit showPrev();
}
