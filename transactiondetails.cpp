#include <transactiondetails.h>
#include <ui_transactiondetails.h>
#include <transactionlist.h>
#include <QStandardItemModel>
#include <QCompleter>
#include <QModelIndex>
#include <QMessageBox>

TransactionDetails::TransactionDetails(QWidget *parent) : QWidget(parent), ui(new Ui::TransactionDetails) {
    ui->setupUi(this);
//    QObject::connect(ui->textSearchEdit, SIGNAL(textChanged(QString)), this, SLOT(editingFinished(QString)));
}

TransactionDetails::~TransactionDetails() {
    delete ui;
}

void TransactionDetails::init(Customer customer) {
    this->customer = customer;

    ui->txtFromCust->setText(customer.name);

    ui->cbFromAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    ui->cbFromAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);


    QSqlQueryModel *toCustModel = DbManager::getInstance()->fetchCustomerList();
    QCompleter *tuCustCompleter = new QCompleter(toCustModel);
    tuCustCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    tuCustCompleter->setCompletionColumn(DB_CUSTOMER_NAME);
    tuCustCompleter->setFilterMode(Qt::MatchContains);
    ui->leToCust->setCompleter(tuCustCompleter);

    ui->cbToAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    ui->cbToAcc->setModelColumn(DB_ACCOUNT_ACCOUNTNR);
}

void TransactionDetails::on_buttonSave_clicked() {
    save(true);
}

void TransactionDetails::save(bool closeWindow) {
    bool success = DbManager::getInstance()->addTransaction(getRecord());
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
