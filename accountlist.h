#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H
#include <QSqlQueryModel>
#include <dbmanager.h>
#include <QDialog>

namespace Ui {
class AccountList;
}

class AccountList : public QDialog
{
    Q_OBJECT

public:
    explicit AccountList(QWidget *parent = 0);
    ~AccountList();
    void init(Customer customer);

signals:
    void showPrev();

private slots:

    void on_Newaccount_clicked();

    void on_backButton_clicked();

private:
    Ui::AccountList *ui;
    Customer customer;
};

#endif // ACCOUNTLIST_H
