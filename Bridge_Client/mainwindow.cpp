#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(800,600);

    login = new Login(this);
    lobby = new Lobby(this);
    connect(login,SIGNAL(stage_change()),lobby,SLOT(show_everything()));
}

MainWindow::~MainWindow()
{

}
