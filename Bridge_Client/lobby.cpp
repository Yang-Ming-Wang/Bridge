#include "lobby.h"

Lobby::Lobby(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(parent);
    label->setText("In Lobby");
    label->setGeometry(600,300,200,100);

    logout = new QPushButton(parent);
    logout->setText("Logout");
    logout->setToolTip("Logout from server");
    logout->setGeometry(300,500,200,100);

    join = new QPushButton(parent);
    join->setText("Join Game");
    join->setToolTip("Join to the Bridge Game");
    join->setGeometry(700,500,200,100);

    connect(logout,SIGNAL(clicked()),this,SLOT(logout_from_server()));
    connect(join,SIGNAL(clicked()),this,SLOT(join_game()));

    hide_everything();
}


void Lobby::hide_everything(void)
{
    label->hide();
    logout->hide();
    join->hide();
}

void Lobby::show_everything(void)
{
    label->show();
    logout->show();
    join->show();
}

void Lobby::logout_from_server(void)
{
    int state = 0;

    hide_everything();
    write(sockfd,&state,sizeof(int));
    emit go_back();
}

void Lobby::setsocket(int sock)
{
    sockfd = sock;
}

void Lobby::join_game(void)
{
    int state = 1;

    hide_everything();
    write(sockfd,&state,sizeof(int));
    emit play_game();
}
