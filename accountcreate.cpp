#include "accountcreate.h"
#include "ui_accountcreate.h"

accountcreate::accountcreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountcreate)
{
    ui->setupUi(this);
}

accountcreate::~accountcreate()
{
    delete ui;
}

void accountcreate::on_closeButton_clicked()
{
    close();
    emit showPrev();
}
