#ifndef TRANSACTIONDETAILS_H
#define TRANSACTIONDETAILS_H

#include <QWidget>

namespace Ui {
class TransactionDetails;
}

class TransactionDetails : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionDetails(QWidget *parent = 0);
    ~TransactionDetails();

private slots:
    void on_buttonLagre_clicked();
    void on_buttonBack_clicked();

signals:
    void showPrev();

private:
    Ui::TransactionDetails *ui;
};

#endif // TRANSACTIONDETAILS_H
