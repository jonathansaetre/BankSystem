#include <transactionlist.h>
#include <ui_transactionlist.h>
#include <transactiondetails.h>


TransactionList::TransactionList(QWidget *parent) : QWidget(parent), ui(new Ui::TransactionList) {
    ui->setupUi(this);
    setWindowTitle("Transactions");
    ui->transactionList->hideColumn(DB_TRANSACTION_ID);
    ui->transactionList->hideColumn(DB_TRANSACTION_FROMACCOUNTID);
    ui->transactionList->hideColumn(DB_TRANSACTION_TOACCOUNTID);
}

TransactionList::~TransactionList() {
    delete ui;
}

void TransactionList::init() {
    ui->transactionList->setModel(DbManager::getInstance()->fetchTransactionList());
    ui->labelCustomer->hide();
    ui->textCustomerName->hide();
}

void TransactionList::init(Customer customer) {
    this->customer = customer;
    ui->textCustomerName->setText(customer.name);
    ui->transactionList->setModel(DbManager::getInstance()->fetchTransactionList(customer.id));
}

void TransactionList::on_buttonNewTransaction_clicked() {
    hide();
    TransactionDetails *transDet = new TransactionDetails();
    if(customer.id.isEmpty()) transDet->init();
    else transDet->init(customer);
    QObject::connect(transDet, SIGNAL(showPrev()), SLOT(showTransactionList()));
    transDet->show();
}

void TransactionList::showTransactionList() {
    if(customer.id.isEmpty()) ui->transactionList->setModel(DbManager::getInstance()->fetchTransactionList());
    else ui->transactionList->setModel(DbManager::getInstance()->fetchTransactionList(customer.id));
    show();
}

void TransactionList::on_buttonBack_clicked() {
    close();
    emit showPrev();
}
