#include "client.h"

Client::Client(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1280,720);

    login = new Login(this);
    lobby = new Lobby(this);
    game = new GameStage(this);
    final = new FinalScreen(this);

    connect(login,SIGNAL(stage_change()),this,SLOT(ChangeState()));
    connect(lobby,SIGNAL(go_back()),this,SLOT(ChangeState()));
    connect(lobby,SIGNAL(play_game()),game,SLOT(game_start()));
    connect(game,SIGNAL(goto_final(int)),final,SLOT(show_everything(int)));
    connect(final,SIGNAL(back_to_lobby()),lobby,SLOT(show_everything()));

    stack = new QStackedWidget;
    stack->addWidget(login);
    stack->addWidget(lobby);

    mainlayout = new QVBoxLayout;
    mainlayout->addWidget(stack);

    setLayout(mainlayout);
}

Client::~Client()
{

}

bool Client::connectIP(QString str)
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

void Client::ChangeState(void)
{
    int index = stack->currentIndex();
    qInfo("index %d",index);
    switch (index) {
    case 0:
        stack->setCurrentIndex(1);
        lobby->show_everything();
        break;
    case 1:
        stack->setCurrentIndex(0);
        break;
    case 2:

        break;
    default:
        break;
    }

}
