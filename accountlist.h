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
    void accounts(QSqlQueryModel *model);
     void customerName(QString name);

signals:
    void showPrev();

private slots:
    void on_cancelButton_clicked();


    void on_Newaccount_clicked();

private:
    Ui::AccountList *ui;
};

#endif // ACCOUNTLIST_H
