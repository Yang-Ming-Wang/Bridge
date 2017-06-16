#include "gamestage.h"

GameStage::GameStage(QWidget *parent) : QWidget(parent)
{
    int i;
    for (i = 0; i < 13; i++) {
        card[i] = new Card(parent,i);
        card[i]->move(100 + 75*i,500);
        card[i]->hide();

        connect(card[i],SIGNAL(selected_card(int,int)),this,SLOT(send_card(int,int)));
    }
    thread = new ClientThread(this,&mutex,&ready);
    connect(thread,SIGNAL(getcard(int)),this,SLOT(show_others(int)));

    other = new Card(parent);
    other->move(100,200);
    other->hide();
}

void GameStage::show_everything(void)
{
    int i,arr[13];
    read(sockfd,arr,sizeof(int) * 13);
    for (i = 0; i < 13; i++) {
        card[i]->setImage(arr[i]);
        card[i]->show();
    }
    thread->start();
}

void GameStage::setsocket(int sock)
{
    sockfd = sock;
    thread->setsocket(sock);
}

void GameStage::send_card(int cardID,int who)
{
    if (thread->notify(cardID)) {
        card[who]->hide();
    }
}

void GameStage::show_others(int otherID)
{
    other->setImage(otherID);
    other->show();
}
