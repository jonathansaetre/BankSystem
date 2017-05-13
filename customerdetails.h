#ifndef CUSTOMERDETAILS_H
#define CUSTOMERDETAILS_H
#include <QWidget>
#include <QSqlQueryModel>
#include <dbmanager.h>

namespace Ui {
class CustomerDetails;
}

class CustomerDetails : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerDetails(QWidget *parent = 0);
    ~CustomerDetails();
    void newCustomer();
    void editCustomer(Customer customer);

signals:
    void showPrev();

private slots:
    void on_buttonCancel_clicked();
    void on_buttonSave_clicked();
    void on_accountButton_clicked();
    void showCustDetails();
    void on_transactionButton_clicked();

private:
    Ui::CustomerDetails *ui;
    Customer customer;
    Customer getRecord();
    void save(bool close);
};

#endif // CUSTOMERDETAILS_H
