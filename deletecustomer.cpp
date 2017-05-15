#include <deletecustomer.h>
#include <ui_deletecustomer.h>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QMessageBox>
#include <QSqlRecord>

Customerdelete::Customerdelete(QWidget *parent) : QDialog(parent), ui(new Ui::Deletecustomer) {
    ui->setupUi(this);
    setFocus();

    QSqlQueryModel *custModel = DbManager::getInstance()->fetchQueryCustomerList();
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

    if(DbManager::getInstance()->updateCustomer(getRecord())){
        QMessageBox::information(this, "Delete customer", "Delete customer successfully");
    } else {
        QMessageBox::information(this, "Delete customerr", "Delete customer failed");
    }

   }

Customer Customerdelete::getRecord() {
    Customer cs;
    cs.id = c.id;
    cs.name = c.name;
    cs.ssn = c.ssn;
    cs.phone = c.phone;
    cs.address = c.address;
    cs.email = c.email;
    cs.state=0;
    return c;
}






void Customerdelete::on_customersnn_editingFinished()
{
    QModelIndex index = ui->customersnn->completer()->currentIndex();
    c = Util::getCustomer(ui->customersnn->completer()->completionModel(), index.row());

}
