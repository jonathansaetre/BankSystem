#ifndef CUSTOMERDETAILS_H
#define CUSTOMERDETAILS_H

#include <QWidget>

namespace Ui {
class CustomerDetails;
}

class CustomerDetails : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerDetails(QWidget *parent = 0);
    ~CustomerDetails();

signals:
    void showPrev();

private slots:
    void on_CloseButton_clicked();

private:
    Ui::CustomerDetails *ui;
};

#endif // CUSTOMERDETAILS_H
