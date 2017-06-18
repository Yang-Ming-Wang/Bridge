#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(1280,720);

    login = new Login(this);
    lobby = new Lobby(this);
    game = new GameStage(this);
    final = new FinalScreen(this);

    connect(login,SIGNAL(stage_change()),lobby,SLOT(show_everything()));
    connect(lobby,SIGNAL(go_back()),login,SLOT(show_everything()));
    connect(lobby,SIGNAL(play_game()),game,SLOT(game_start()));
    connect(game,SIGNAL(goto_final(int)),final,SLOT(show_everything(int)));
    connect(final,SIGNAL(back_to_lobby()),lobby,SLOT(show_everything()));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::connectIP(QString str)
{
    int sockfd;
    struct sockaddr_in servaddr;
    char *connect_ip = str.toLatin1().data();

    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) {
        printf("socket error\n");
        return false;
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9877);

    if (inet_pton(AF_INET,connect_ip,&servaddr.sin_addr) <= 0)
        printf("inet_ption error for %s\n",connect_ip);

    if (::connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) {
        printf("connect error\n");
        return false;
    }
    login->setsocket(sockfd);
    lobby->setsocket(sockfd);
    game->setsocket(sockfd);
    return true;
}
