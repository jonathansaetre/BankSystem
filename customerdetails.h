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
    void editCustomer(QSqlQueryModel *model, int index);

signals:
    void showPrev();

private slots:
    void on_buttonCancel_clicked();
    void on_buttonSave_clicked();
    void on_buttonSave_New_clicked();
    void on_accountButton_clicked();
     void showCustDetails();

     void on_pushButton_clicked();

private:
    Ui::CustomerDetails *ui;
    QString id;
    Customer getRecord();
    void save(bool close);
};

#endif // CUSTOMERDETAILS_H
