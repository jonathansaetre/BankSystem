#include "transactionlist.h"
#include "ui_transactionlist.h"
#include "transactiondetails.h"

TransactionList::TransactionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionList)
{
    ui->setupUi(this);
}

TransactionList::~TransactionList()
{
    delete ui;
}

void TransactionList::on_buttonNewTransaction_clicked()
{
    TransactionDetails *transDet = new TransactionDetails();
    QObject::connect(transDet, SIGNAL(showPrev()), SLOT(show()));
    transDet->show();
}

void TransactionList::on_buttonBack_clicked()
{
    close();
    emit showPrev();
}
