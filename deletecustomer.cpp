#include "deletecustomer.h"
#include "ui_deletecustomer.h"

Deletecustomer::Deletecustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deletecustomer)
{
    ui->setupUi(this);
}

Deletecustomer::~Deletecustomer()
{
    delete ui;
}

void Deletecustomer::on_closeButton_clicked()
{
    close();
    emit showPrev();
}
