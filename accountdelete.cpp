#include "accountdelete.h"
#include "ui_accountdelete.h"

accountdelete::accountdelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountdelete)
{
    ui->setupUi(this);
    setFocus();

    ui->customercomboBox->setModel(DbManager::getInstance()->fetchCustomerList());
    ui->customercomboBox->setModelColumn(DB_CUSTOMER_SSN);

   // ui->customercomboBox->setModel( DbManager::getInstance()->fetchAccountList(ui->customercomboBox->currentText()));
    //ui->customercomboBox->setModelColumn(Util::DB_ACCOUNT_ACCOUNTNR);

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
