#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(800,600);

    login = new Login(this);
}

MainWindow::~MainWindow()
{

}
