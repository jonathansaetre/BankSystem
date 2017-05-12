#include "accountlist.h"
#include "ui_accountlist.h"
#include <accountcreate.h>
#include <QSqlRecord>

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

void AccountList::customerName(QString name){
    ui->customerBox->setText(name);
}

void AccountList::on_Newaccount_clicked()
{
    hide();
    AccountDetails *createaccount = new AccountDetails();
    QObject::connect(createaccount, SIGNAL(showPrev()), SLOT(show()));
    createaccount->show();
}

void AccountList::on_backButton_clicked()
{
    close();
    emit showPrev();
}
