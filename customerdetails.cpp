#include "customerdetails.h"
#include "ui_customerdetails.h"

CustomerDetails::CustomerDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerDetails)
{
    ui->setupUi(this);
}

CustomerDetails::~CustomerDetails()
{
    delete ui;
}

void CustomerDetails::on_CloseButton_clicked()
{
    close();
    emit showPrev();
}
