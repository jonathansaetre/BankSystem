#include <transactiondetails.h>
#include <ui_transactiondetails.h>
#include <transactionlist.h>
#include <QStandardItemModel>
#include <QCompleter>
#include <QModelIndex>
#include <QMessageBox>
#include <QAbstractProxyModel>

TransactionDetails::TransactionDetails(QWidget *parent) : QWidget(parent), ui(new Ui::TransactionDetails) {
    ui->setupUi(this);
    setWindowTitle("New transaction");

    custModel = DbManager::getInstance()->fetchStandardCustomerList();

    ui->cbFromCust->setModel(custModel);
    ui->cbFromCust->setEditable(true);
    ui->cbFromCust->setModelColumn(DB_CUSTOMER_NAME);
    ui->cbFromCust->setCompleter(new QCompleter(custModel));
    ui->cbFromCust->completer()->setCaseSensitivity(Qt::CaseInsensitive);
    ui->cbFromCust->completer()->setCompletionColumn(DB_CUSTOMER_NAME);
    ui->cbFromCust->completer()->setFilterMode(Qt::MatchContains);

    ui->cbFromAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);

    ui->cbToCust->setModel(custModel);
    ui->cbToCust->setEditable(true);
    ui->cbToCust->setModelColumn(DB_CUSTOMER_NAME);
    ui->cbToCust->setCompleter(new QCompleter(custModel));
    ui->cbToCust->completer()->setCaseSensitivity(Qt::CaseInsensitive);
    ui->cbToCust->completer()->setCompletionColumn(DB_CUSTOMER_NAME);
    ui->cbToCust->completer()->setFilterMode(Qt::MatchContains);

    ui->cbToAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
}

TransactionDetails::~TransactionDetails() {
    delete ui;
}

void TransactionDetails::init() {
    ui->labelCustomerName->hide();
    ui->textCustomerName->hide();
}

void TransactionDetails::init(Customer customer) {
    this->customer = customer;
    ui->cbFromCust->setDisabled(true);
    ui->textCustomerName->setText(customer.name);
    ui->cbFromAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    ui->cbToAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));

    if(ui->cbFromAcc->model()->rowCount() == 0) QMessageBox::information(this, "Transaction", customer.name + " has none accounts");
}

void TransactionDetails::on_buttonSave_clicked() {
    save(true);
}

void TransactionDetails::save(bool closeWindow) {
    if(ui->cbFromAcc->currentIndex() < 0 || ui->cbToAcc->currentIndex() < 0 || !Util::isNumber(ui->leAmount->text()) || ui->leAmount->text().toInt() <= 0) {
        QMessageBox::information(this, "Account", "Missing source account, target account or amount.");
        return;
    }
    Transaction transaction = getRecord();
    bool success = DbManager::getInstance()->addTransaction(transaction);
    if(success) {
        if(closeWindow) {
            close();
            emit showPrev();
        } else {
            if(customer.id.isEmpty()) {
                ui->cbFromCust->clear();
                ui->cbFromAcc->clear();
            }
            ui->cbToCust->clear();
            ui->cbToAcc->clear();
            ui->leAmount->clear();
        }
    } else {
        QMessageBox::information(this, "New transaction", "New transaction failed");
    }
}

Transaction TransactionDetails::getRecord() {
    Account fromAccount = Util::getAccount(ui->cbFromAcc->model(), ui->cbFromAcc->currentIndex());
    Account toAccount = Util::getAccount(ui->cbToAcc->model(), ui->cbToAcc->currentIndex());

    Transaction transaction;
    transaction.fromAccountID = fromAccount.id;
    transaction.toAccountID = toAccount.id;
    transaction.amount = ui->leAmount->text().toInt();
    return transaction;
}

void TransactionDetails::on_buttonCancel_clicked() {
    close();
    emit showPrev();
}

void TransactionDetails::on_cbToCust_activated(int index) {
    Customer cust = Util::getCustomer(ui->cbToCust->model(), index);
    ui->cbToAcc->setModel(DbManager::getInstance()->fetchAccountList(cust.id));
    ui->cbToAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
    if(ui->cbToAcc->model()->rowCount() == 0) QMessageBox::information(this, "Transaction", cust.name + " has none accounts");
}

void TransactionDetails::on_cbFromCust_activated(int index) {
    Customer cust = Util::getCustomer(ui->cbFromCust->model(), index);
    ui->cbFromAcc->setModel(DbManager::getInstance()->fetchAccountList(cust.id));
    ui->cbFromAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
    if(ui->cbFromAcc->model()->rowCount() == 0) QMessageBox::information(this, "Transaction", cust.name + " has none accounts");
}
