#ifndef TRANSACTIONDETAILS_H
#define TRANSACTIONDETAILS_H
#include <QWidget>
#include <dbmanager.h>

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

private slots:
    void on_buttonSave_clicked();
    void on_leToCust_editingFinished();
    void on_buttonCancel_clicked();

signals:
    void showPrev();

private:
    Ui::TransactionDetails *ui;
    Customer customer;
    Transaction getRecord();
    void save(bool close);
};

#endif // TRANSACTIONDETAILS_H
