#ifndef TRANSACTIONLIST_H
#define TRANSACTIONLIST_H

#include <QWidget>

namespace Ui {
class TransactionList;
}

class TransactionList : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionList(QWidget *parent = 0);
    ~TransactionList();

private slots:
    void on_buttonNewTransaction_clicked();

    void on_buttonBack_clicked();

signals:
    void showPrev();

private:
    Ui::TransactionList *ui;
};

#endif // TRANSACTIONLIST_H
