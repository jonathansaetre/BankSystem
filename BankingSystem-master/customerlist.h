#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlQuery>

namespace Ui {
class CustomerList;
}

class CustomerList : public QWidget
{
    Q_OBJECT


public:
    explicit CustomerList(QWidget *parent = 0);
    ~CustomerList();

private slots:
    void on_buttonBack_clicked();
    void on_buttonNewCustomer_clicked();
    void textSeachEditChanged(QString text);
    void custListDoubleClicked(QModelIndex);
    void showCustList();

signals:
    void showPrev();

private:
    Ui::CustomerList *ui;
    QSqlQueryModel *model;
};

#endif // CUSTOMERLIST_H
