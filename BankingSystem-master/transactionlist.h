#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H
#include <QWidget>
#include <dbmanager.h>

namespace Ui {
class TransactionList;
}

class TransactionList : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionList(QWidget *parent = 0);
    ~TransactionList();
    void init(Customer customer);

private slots:
    void on_buttonNewTransaction_clicked();
    void on_buttonBack_clicked();
    void showTransactionList();

signals:
    void showPrev();

private:
    Ui::TransactionList *ui;
    Customer customer;
};

#endif // TRANSACTIONLIST_H
