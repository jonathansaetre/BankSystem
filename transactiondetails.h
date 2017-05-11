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
    void on_buttonLagre_clicked();
    void on_buttonBack_clicked();

    void on_buttonSave_clicked();

    void on_leToCust_editingFinished();

signals:
    void showPrev();

private:
    Ui::TransactionDetails *ui;
    Customer customer;
};

#endif // TRANSACTIONDETAILS_H
