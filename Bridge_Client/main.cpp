#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    bool success;

    if (QCoreApplication::arguments().size() == 2) {
        success = w.connectIP(QCoreApplication::arguments().at(1));
    } else {
        success = w.connectIP(QString("127.0.0.1"));
    }
    if (!success) {
        return -1;
    }
    w.show();

    return a.exec();
}
