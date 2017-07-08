#include "lobby.h"

Lobby::Lobby(QWidget *parent) : Subscriber(parent)
{
    QFont font;
    font.setPointSize(14);

    label = new QLabel(this);
    label->setText("In Lobby");
    label->setGeometry(80,50,150,50);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(font);

    logout = new QPushButton(this);
    logout->setText("Logout");
    logout->setToolTip("Logout from server");
    logout->setGeometry(300,500,200,100);

    join = new QPushButton(this);
    join->setText("Join Game");
    join->setToolTip("Join to the Bridge Game");
    join->setGeometry(700,500,200,100);

    refresh = new QPushButton(this);
    refresh->setText("refresh");
    refresh->setToolTip("get online user infomation right now!!");
    refresh->setGeometry(800,100,100,50);

    int i;
    for (i = 0;i < 8;i++) {
        user[i] = new QLabel(this);
        user[i]->setText("");
        user[i]->setGeometry(300,50 + 50*i,360,50);
        user[i]->setStyleSheet("QLabel {color:green}");
        user[i]->setFont(font);
    }

    connect(logout,SIGNAL(clicked()),this,SLOT(logout_from_server()));
    connect(join,SIGNAL(clicked()),this,SLOT(join_game()));
    connect(refresh,SIGNAL(clicked()),this,SLOT(refresh_data()));

}

void Lobby::logout_from_server(void)
{
    thread->logout();
    emit stage_change(0);
}

void Lobby::join_game(void)
{
    thread->join_game();
    emit stage_change(2);
}

void Lobby::refresh_data()
{
    int i,loginnum,win[8],lose[8];
    char account[8][15];

    loginnum = thread->refresh_data(account,win,lose);

    for (i = 0;i < loginnum;i++) {
        QString str(QString::fromLatin1(account[i]) + "  " \
                    + QString::number(win[i]) + "  " + QString::number(lose[i]));
        user[i]->setText(str);
    }

    while (i < 8) {
        user[i]->setText("");
        i += 1;
    }
}
