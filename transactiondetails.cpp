#include <transactiondetails.h>
#include <ui_transactiondetails.h>
#include <transactionlist.h>
#include <QStandardItemModel>
#include <QCompleter>
#include <QModelIndex>

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
    ui->cbFromAcc->setModelColumn(Util::DB_ACCOUNT_ACCOUNTNR);


    QSqlQueryModel *toCustModel = DbManager::getInstance()->fetchCustomerList();
    QCompleter *tuCustCompleter = new QCompleter(toCustModel);
    tuCustCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    tuCustCompleter->setCompletionColumn(Util::DB_CUSTOMER_NAME);
    tuCustCompleter->setFilterMode(Qt::MatchContains);
    ui->leToCust->setCompleter(tuCustCompleter);
}

void TransactionDetails::on_buttonLagre_clicked() {

}

void TransactionDetails::on_buttonBack_clicked() {
    close();
    emit showPrev();
}

void TransactionDetails::on_buttonSave_clicked() {
//    bool success;
//    if(id.isEmpty()) success = DbManager::getInstance()->addCustomer(getRecord());
//    else success = DbManager::getInstance()->updateCustomer(getRecord());
//    if(success) {
//        if(closeWindow) {
//            close();
//            emit showPrev();
//        } else {
//            foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
//                widget->clear();
//            }
//        }
//    } else {
//        QString action = id.isEmpty() ? "Add" : "Update";
//        QMessageBox::information(this, action + " ", action + " customer failed");
//    }
}

//Transaction TransactionDetails::getRecord() {
//    Transaction t;
//    t.fromAccountnr = ui->nameBox->text();
//    t.ssn = ui->ssnBox->text();
//    t.phone = ui->phoneBox->text();
//    t.address = ui->addressBox->text();
//    t.email = ui->emailBox->text();
//    return t;
//}

void TransactionDetails::on_leToCust_editingFinished() {
    QModelIndex index = ui->leToCust->completer()->currentIndex();
    if(!index.isValid()) {
        ui->leToCust->clear();
        ui->cbToAcc->clear();
        return;
    }
    Customer cust = Util::getCustomer(ui->leToCust->completer()->completionModel(), index.row());
    ui->cbToAcc->setModel(DbManager::getInstance()->fetchAccountList(customer.id));
    ui->cbToAcc->setModelColumn(Util::DB_ACCOUNT_ACCOUNTNR);
}
