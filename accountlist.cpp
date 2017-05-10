#include "accountlist.h"
#include "ui_accountlist.h"
#include <QSqlRecord>
#include <c.cpp>

AccountList::AccountList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountList)
{
    ui->setupUi(this);
}

AccountList::~AccountList()
{
    delete ui;
}

void AccountList::accounts(QSqlQueryModel *model) {

    ui->accountList->setModel(model);
    ui->customerBox->setText(model->record(1).value(C::DB_ACCOUNT_NAME).toString());

}

void AccountList::on_cancelButton_clicked()
{
    close();
    emit showPrev();
}
