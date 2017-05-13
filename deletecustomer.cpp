#include <deletecustomer.h>
#include <ui_deletecustomer.h>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMessageBox>
#include <QSqlRecord>

Customerdelete::Customerdelete(QWidget *parent) : QDialog(parent), ui(new Ui::Deletecustomer) {
    ui->setupUi(this);
    setFocus();

    QSqlQueryModel *custModel = DbManager::getInstance()->fetchCustomerList();
    QCompleter *custCompleter = new QCompleter(custModel);
    custCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    custCompleter->setCompletionColumn(DB_CUSTOMER_NAME);
    custCompleter->setFilterMode(Qt::MatchContains);

    ui->customersnn->setCompleter(custCompleter);
    //ui->nameBox->setModelColumn(DB_CUSTOMER_NAME);
}

Customerdelete::~Customerdelete() {
    delete ui;
}

void Customerdelete::on_closeButton_clicked() {
    close();
    emit showPrev();
}

void Customerdelete::on_deleteButton_clicked() {
    QModelIndex index = ui->customersnn->completer()->currentIndex();
    Customer c = Util::getCustomer(ui->customersnn->completer()->completionModel(), index.row());
    c.state=0;
    if(DbManager::getInstance()->updateCustomer(c)){
        QMessageBox::information(this, "Delete customer", "Delete customer successfully");
    } else {
        QMessageBox::information(this, "Delete customerr", "Delete customer failed");
    }


}



