#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(1280,720);

    int sockfd;

    login = new Login(this);
    sockfd = login->getsocket();

    lobby = new Lobby(this);
    lobby->setsocket(sockfd);
    game = new GameStage(this);
    game->setsocket(sockfd);

    connect(login,SIGNAL(stage_change()),lobby,SLOT(show_everything()));
    connect(lobby,SIGNAL(go_back()),login,SLOT(show_everything()));
    connect(lobby,SIGNAL(play_game()),game,SLOT(show_everything()));
}

MainWindow::~MainWindow()
{

}
