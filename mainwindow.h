#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonCustomers_clicked();
    void on_buttonTransactions_clicked();
    void on_actionNew_triggered();
    void on_actionDelete_triggered();
    void on_actionNew_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
