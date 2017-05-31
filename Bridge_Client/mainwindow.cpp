#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(1600,1200);

    int sockfd;

    login = new Login(this);
    sockfd = login->getsocket();
    lobby = new Lobby(this);
    lobby->setsocket(sockfd);

    connect(login,SIGNAL(stage_change()),lobby,SLOT(show_everything()));
    connect(lobby,SIGNAL(go_back()),login,SLOT(show_everything()));
}

MainWindow::~MainWindow()
{

}
