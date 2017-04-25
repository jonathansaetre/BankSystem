#include "customerlist.h"
#include "ui_customerlist.h"
#include "customerdetails.h"

CustomerList::CustomerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerList)
{
    ui->setupUi(this);
}

CustomerList::~CustomerList()
{
    delete ui;
}

void CustomerList::on_buttonBack_clicked()
{
    this->close();
    emit showPrev();
}
void CustomerList::on_buttonNewCustomer_clicked()
{
    CustomerDetails *CusDetai = new CustomerDetails();
    QObject::connect(CusDetai, SIGNAL(showPrev()), SLOT(show()));
    CusDetai->show();
}

