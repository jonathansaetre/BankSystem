#include <transactiondetails.h>
#include <ui_transactiondetails.h>
#include <transactionlist.h>
#include <QStandardItemModel>
#include <QCompleter>
#include <QModelIndex>
#include <QMessageBox>

TransactionDetails::TransactionDetails(QWidget *parent) : QWidget(parent), ui(new Ui::TransactionDetails) {
    ui->setupUi(this);

    QSqlQueryModel *custModel = DbManager::getInstance()->fetchCustomerList();
    QCompleter *custCompleter = new QCompleter(custModel);
    custCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    custCompleter->setCompletionColumn(DB_CUSTOMER_NAME);
    custCompleter->setFilterMode(Qt::MatchContains);

    ui->leFromCust->setCompleter(custCompleter);
    ui->cbFromAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
    ui->leToCust->setCompleter(custCompleter);
    ui->cbToAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
    ui->date->setDate(QDate::currentDate());
    ui->leAmount->setInputMask("D000000000");
    ui->leAmount->setCursorPosition(0);
}

TransactionDetails::~TransactionDetails() {
    delete ui;
}

void TransactionDetails::init(Customer customer) {
    this->customer = customer;
    ui->leFromCust->setText(customer.name);
    ui->cbFromAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    ui->leToCust->setPlaceholderText("Internal transfer");
    ui->cbToAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
}

void TransactionDetails::on_buttonSave_clicked() {
    save(true);
}

void TransactionDetails::save(bool closeWindow) {
//    if(!ui->leAmount->v)
    Transaction transaction = getRecord();
//    if()
    bool success = DbManager::getInstance()->addTransaction(transaction);
    if(success) {
        if(closeWindow) {
            close();
            emit showPrev();
        } else {
            if(customer.id.isEmpty()) {
                ui->leFromCust->clear();
                ui->cbFromAcc->clear();
            }
            ui->leToCust->clear();
            ui->cbToAcc->clear();
            ui->date->setDate(QDate::currentDate());
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
    transaction.date = ui->date->date();
//    transaction.amount = 10;
    return transaction;
}

void TransactionDetails::on_leToCust_editingFinished() {
    QModelIndex index = ui->leToCust->completer()->currentIndex();
    if(!index.isValid()) {
        ui->leToCust->clear();
        ui->cbToAcc->clear();
        return;
    }
    Customer cust = Util::getCustomer(ui->leToCust->completer()->completionModel(), index.row());
    ui->cbToAcc->setModel(DbManager::getInstance()->fetchAccountList(cust.id));
    ui->cbToAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
}

void TransactionDetails::on_buttonCancel_clicked() {
    close();
    emit showPrev();
}
