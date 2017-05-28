#include "lobby.h"

Lobby::Lobby(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(parent);
    label->setText("In Lobby");
    label->setGeometry(400,300,200,100);

    hide_everything();
}


void Lobby::hide_everything(void)
{
    label->hide();
}

void Lobby::show_everything(void)
{
    qDebug("recv singal");
    label->show();
}
