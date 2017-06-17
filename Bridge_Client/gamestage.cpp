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
    thread = new ClientThread(this);
    connect(thread,SIGNAL(getcard(int)),this,SLOT(show_others(int)));

    other = new Card(parent);
    other->move(100,200);
    other->hide();

    QFont font;
    font.setPointSize(14);
    status = new QLabel(parent);
    status->setGeometry(500,250,300,100);
    status->setFont(font);
    connect(thread,SIGNAL(change_turn(int)),this,SLOT(change_turn(int)));
}

void GameStage::show_everything(void)
{
    int i,arr[13];
    read(sockfd,arr,sizeof(int) * 13);
    for (i = 0; i < 13; i++) {
        card[i]->setImage(arr[i]);
        card[i]->show();
    }
    status->show();
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
    } else {
        status->setStyleSheet("QLabel {color:red}");
        status->setText("It's not your turn!!");
    }
}

void GameStage::show_others(int otherID)
{
    other->setImage(otherID);
    other->show();
}

void GameStage::change_turn(int turn)
{
    if (turn == 0) {
        status->setStyleSheet("QLabel {color:green}");
        status->setText("Your Turn");
    } else {
        status->setStyleSheet("QLabel {}");
        status->setText("Wait for others");
    }
}
