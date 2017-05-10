#include "accountlist.h"
#include "ui_accountlist.h"
#include <accountcreate.h>
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
}

void AccountList::on_cancelButton_clicked()
{
    close();
    emit showPrev();
}

void AccountList::on_Newaccount_clicked()
{
    hide();
    AccountCreate *createaccount = new AccountCreate();
    QObject::connect(createaccount, SIGNAL(showPrev()), SLOT(show()));
    createaccount->show();
}
