#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H
#include <QWidget>
#include <QSqlDatabase>
namespace Ui {
class CustomerList;
}

class CustomerList : public QWidget
{
    Q_OBJECT
public:
    void openDB(){
        BankSyst= QSqlDatabase::addDatabase("QSQLITE");
         BankSyst.setDatabaseName("BankingSystem.sqlite");

    }
    void closeDB(){
        BankSyst.close();
    }

public:
    explicit CustomerList(QWidget *parent = 0);
    ~CustomerList();

private slots:
    void on_buttonBack_clicked();

    void on_buttonNewCustomer_clicked();

    void on_loadcust_clicked();

signals:
    void showPrev();

private:
    Ui::CustomerList *ui;
QSqlDatabase BankSyst;
};

#endif // CUSTOMERLIST_H
