#include "lobby.h"

Lobby::Lobby(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(parent);
    label->setText("In Lobby");
    label->setGeometry(300,300,200,100);

    logout = new QPushButton(parent);
    logout->setText("Logout");
    logout->setToolTip("Logout from server");
    logout->setGeometry(300,500,200,100);

    join = new QPushButton(parent);
    join->setText("Join Game");
    join->setToolTip("Join to the Bridge Game");
    join->setGeometry(700,500,200,100);

    refresh = new QPushButton(parent);
    refresh->setText("refresh");
    refresh->setToolTip("get online user infomation right now!!");
    refresh->setGeometry(800,100,100,50);

    int i;
    for (i = 0;i < 8;i++) {
        user[i] = new QLabel(parent);
        user[i]->setText("");
        user[i]->setGeometry(600,100 + 50*i,100,50);
        user[i]->hide();
    }

    connect(logout,SIGNAL(clicked()),this,SLOT(logout_from_server()));
    connect(join,SIGNAL(clicked()),this,SLOT(join_game()));
    connect(refresh,SIGNAL(clicked()),this,SLOT(refresh_data()));

    hide_everything();
}


void Lobby::hide_everything(void)
{
    int i;
    for (i = 0;i < 8;i++) {
        user[i]->hide();
    }

    label->hide();
    logout->hide();
    join->hide();
    refresh->hide();
}

void Lobby::show_everything(void)
{
    int i;

    label->show();
    logout->show();
    join->show();
    refresh->show();

    get_online_info();
    for (i = 0;i < 8;i++) {
        user[i]->show();
    }
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

void Lobby::get_online_info()
{
    int i,loginnum;
    char account[15];

    for (i = 0;i < 8;i++) {
        user[i]->setText("");
    }

    read(sockfd,&loginnum,sizeof(int));

    for (i = 0;i < loginnum;i++) {
        read(sockfd,account,sizeof(char) * 15);
        user[i]->setText(account);
    }
}

void Lobby::refresh_data()
{
    int state = 2;
    write(sockfd,&state,sizeof(int));
    get_online_info();
}
