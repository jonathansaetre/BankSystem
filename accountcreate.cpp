#include <accountcreate.h>
#include <ui_accountcreate.h>

AccountCreate::AccountCreate(QWidget *parent) : QDialog(parent), ui(new Ui::accountcreate) {
    ui->setupUi(this);
}

AccountCreate::~AccountCreate() {
    delete ui;
}

void AccountCreate::on_closeButton_clicked() {
    close();
    emit showPrev();
}
