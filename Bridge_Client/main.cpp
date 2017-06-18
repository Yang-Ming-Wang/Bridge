#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if (QCoreApplication::arguments().size() == 2) {
        w.connectIP(QCoreApplication::arguments().at(1));
    } else {
        w.connectIP(QString("127.0.0.1"));
    }
    w.show();

    return a.exec();
}
