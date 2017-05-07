#include <mainwindow.h>
#include <QApplication>
#include <dbmanager.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int r = a.exec();
    DbManager::close();
    return r;
}

