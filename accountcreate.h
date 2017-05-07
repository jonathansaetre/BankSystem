#ifndef ACCOUNTCREATE_H
#define ACCOUNTCREATE_H
#include<QSqlQueryModel>
#include <dbmanager.h>
#include <QDialog>

namespace Ui {
class accountcreate;
}

class AccountCreate : public QDialog
{
    Q_OBJECT

public:
    explicit AccountCreate(QWidget *parent = 0);
    ~AccountCreate();

private slots:
    void on_closeButton_clicked();
    void on_comboAccount_currentIndexChanged();
    void on_addButton_clicked();

signals:
    void showPrev();

private:
    Ui::accountcreate *ui;
     QSqlQueryModel *model;
};

#endif // ACCOUNTCREATE_H
