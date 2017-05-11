#include "accountdelete.h"
#include "ui_accountdelete.h"

accountdelete::accountdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountdelete)
{
    ui->setupUi(this);
    setFocus();
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
