#include "lobby.h"

Lobby::Lobby(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(parent);
    label->setText("In Lobby");
    label->setGeometry(400,300,200,100);

    logout = new QPushButton(parent);
    logout->setText("Logout");
    logout->setToolTip("Logout from server");
    logout->setGeometry(300,400,200,100);

    connect(logout,SIGNAL(clicked()),this,SLOT(logout_from_server()));

    hide_everything();
}


void Lobby::hide_everything(void)
{
    label->hide();
    logout->hide();
}

void Lobby::show_everything(void)
{
    label->show();
    logout->show();
}

void Lobby::logout_from_server(void)
{
    hide_everything();
    emit go_back();
}
