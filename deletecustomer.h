#ifndef DELETECUSTOMER_H
#define DELETECUSTOMER_H
#include<qsqlquerymodel.h>
#include <QDialog>

namespace Ui {
class Deletecustomer;
}

class Deletecustomer : public QDialog
{
    Q_OBJECT

public:
    explicit Deletecustomer(QWidget *parent = 0);
    ~Deletecustomer();

private slots:
    void on_closeButton_clicked();

    void on_combocustomer_currentIndexChanged(const QString &arg1);

    void on_deleteButton_clicked();

signals:
    void showPrev();

private:
    Ui::Deletecustomer *ui;
    QSqlQueryModel *model;

};

#endif // DELETECUSTOMER_H
