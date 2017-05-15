#ifndef TRANSACTIONDETAILS_H
#define TRANSACTIONDETAILS_H
#include <QWidget>
#include <dbmanager.h>
#include <QComboBox>

namespace Ui {
class TransactionDetails;
}

class TransactionDetails : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionDetails(QWidget *parent = 0);
    ~TransactionDetails();
    void init(Customer customer);
    void init();

private slots:
    void on_buttonSave_clicked();
    void on_buttonCancel_clicked();
    void on_cbToCust_activated(int index);

    void on_cbFromCust_activated(int index);

signals:
    void showPrev();

private:
    Ui::TransactionDetails *ui;
    Customer customer;
    QStandardItemModel *custModel;
    Transaction getRecord();
    void save(bool close);
//    void setCbCustProperties(QComboBox& cb);
};

#endif // TRANSACTIONDETAILS_H
