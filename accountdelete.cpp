#include "accountdelete.h"
#include "ui_accountdelete.h"

accountdelete::accountdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountdelete)
{
    ui->setupUi(this);
}

accountdelete::~accountdelete()
{
    delete ui;
}
