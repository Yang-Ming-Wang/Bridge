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
    final = new FinalScreen(this);

    connect(login,SIGNAL(stage_change()),lobby,SLOT(show_everything()));
    connect(lobby,SIGNAL(go_back()),login,SLOT(show_everything()));
    connect(lobby,SIGNAL(play_game()),game,SLOT(game_start()));
    connect(game,SIGNAL(goto_final(int)),final,SLOT(show_everything(int)));
}

MainWindow::~MainWindow()
{

}
