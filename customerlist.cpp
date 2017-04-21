#include "customerlist.h"
#include "ui_customerlist.h"

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

}
