#ifndef ACCOUNTCREATE_H
#define ACCOUNTCREATE_H

#include <QDialog>

namespace Ui {
class accountcreate;
}

class accountcreate : public QDialog
{
    Q_OBJECT

public:
    explicit accountcreate(QWidget *parent = 0);
    ~accountcreate();

private slots:
    void on_closeButton_clicked();

signals:
    void showPrev();

private:
    Ui::accountcreate *ui;
};

#endif // ACCOUNTCREATE_H
