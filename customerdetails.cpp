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
