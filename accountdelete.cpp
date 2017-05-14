#include "accountdelete.h"
#include "ui_accountdelete.h"
#include <QCompleter>
accountdelete::accountdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountdelete)
{
    ui->setupUi(this);
    setFocus();

    QSqlQueryModel *custModel = DbManager::getInstance()->fetchQueryCustomerList();
    QCompleter *custCompleter = new QCompleter(custModel);
    custCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    custCompleter->setCompletionColumn(DB_CUSTOMER_NAME);
    custCompleter->setFilterMode(Qt::MatchContains);

    ui->customername->setCompleter(custCompleter);
    ui->accountcomboBox->setModelColumn(DB_ACCOUNT_ACCOUNTNR);


}

accountdelete::~accountdelete()
{
    delete ui;
}


void accountdelete::on_cancelButton_clicked()
{
    close();
    emit showPrev();
}

void accountdelete::on_customername_editingFinished()
{
    QModelIndex index = ui->customername->completer()->currentIndex();
    if(!index.isValid()) {
        ui->customername->clear();
        return;
    }
    Customer cust = Util::getCustomer(ui->customername->completer()->completionModel(), index.row());
    ui->accountcomboBox->setModel(DbManager::getInstance()->fetchAccountList(cust.id));
}
