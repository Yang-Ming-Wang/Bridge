#include "client.h"

Client::Client(QWidget *parent) : QWidget(parent)
{
    resize(1280,720);

    login = new Login(this);
    lobby = new Lobby(this);
    game = new GameStage(this);
    final = new FinalScreen(this);
    waitscreen = new WaitingScreen(this);
    thread = new ClientThread(this);
    game->setThread(thread);

    connect(login,SIGNAL(stage_change(int)),this,SLOT(ChangeState(int)));
    connect(lobby,SIGNAL(stage_change(int)),this,SLOT(ChangeState(int)));
    connect(game,SIGNAL(stage_change(int)),this,SLOT(ChangeState(int)));
    connect(final,SIGNAL(stage_change(int)),this,SLOT(ChangeState(int)));

    connect(thread,SIGNAL(getcard(int,int)),game,SLOT(show_others(int,int)));
    connect(thread,SIGNAL(your_turn(bool)),game,SLOT(your_turn(bool)));
    connect(thread,SIGNAL(game_start(int*)),game,SLOT(show_everything(int*)));
    connect(thread,SIGNAL(result(int)),game,SLOT(hide_everything(int)));

    stack = new QStackedWidget;
    stack->addWidget(login);
    stack->addWidget(lobby);
    stack->addWidget(waitscreen);
    stack->addWidget(game);
    stack->addWidget(final);

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
    thread->setsocket(sockfd);
    return true;
}

void Client::ChangeState(int nextState)
{
    switch (nextState) {
    case 0:
        break;
    case 1:
        lobby->get_online_info();
        break;
    case 2:
        thread->start();
        break;
    case 3:
        break;
    case 4:
        final->setWinner(1);
        break;
    case 5:
        nextState = 4;
        final->setWinner(0);
        break;
    }
    stack->setCurrentIndex(nextState);
}
