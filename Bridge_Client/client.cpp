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

    login->attach(thread);
    lobby->attach(thread);
    game->attach(thread);

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
    return thread->connectIP(str);
}

void Client::ChangeState(int nextState)
{
    switch (nextState) {
    case 0:
        break;
    case 1:
        lobby->refresh_data();
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
