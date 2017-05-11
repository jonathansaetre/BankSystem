#ifndef ACCOUNTDELETE_H
#define ACCOUNTDELETE_H
#include <dbmanager.h>
#include <QDialog>

namespace Ui {
class accountdelete;
}

class accountdelete : public QDialog
{
    Q_OBJECT

public:
    explicit accountdelete(QWidget *parent = 0);
    ~accountdelete();

signals:
    void showPrev();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::accountdelete *ui;
};

#endif // ACCOUNTDELETE_H
