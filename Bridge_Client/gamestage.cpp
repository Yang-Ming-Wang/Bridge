#include "gamestage.h"

GameStage::GameStage(QWidget *parent) : QWidget(parent)
{
    int i;
    for (i = 0; i < 13; i++) {
        card[i] = new Card(parent);
        card[i]->move(100 + 75*i,500);
        card[i]->hide();

        connect(card[i],SIGNAL(selected_card(int)),this,SLOT(send_card(int)));
    }
}

void GameStage::show_everything(void)
{
    int i,arr[13];
    read(sockfd,arr,sizeof(int) * 13);
    for (i = 0; i < 13; i++) {
        card[i]->setImage(arr[i]);
        card[i]->show();
        qInfo("recieve [%d] card\n",arr[i]);
    }
}

void GameStage::setsocket(int sock)
{
    sockfd = sock;
}

void GameStage::send_card(int cardID)
{
    qInfo("send [%d] card\n",cardID);
}
