#ifndef ACCOUNTCREATE_H
#define ACCOUNTCREATE_H
#include<QSqlQueryModel>
#include <dbmanager.h>
#include <QDialog>

namespace Ui {
class accountcreate;
}

class AccountDetails : public QDialog
{
    Q_OBJECT

public:
    explicit AccountDetails(QWidget *parent = 0);
    ~AccountDetails();

private slots:
    void on_comboAccount_currentIndexChanged();
    void on_saveButton_clicked();
    void on_closeButton_clicked();

signals:
    void showPrev();

private:
    Ui::accountcreate *ui;
     QSqlQueryModel *model;
};

#endif // ACCOUNTCREATE_H
