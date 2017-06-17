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
    connect(thread,SIGNAL(getcard(int,int)),this,SLOT(show_others(int,int)));
    connect(thread,SIGNAL(your_turn(bool)),this,SLOT(your_turn(bool)));
    connect(thread,SIGNAL(game_start(int*)),this,SLOT(show_everything(int*)));
    connect(thread,SIGNAL(result(int)),this,SLOT(hide_everything(int)));

    other[0] = new Card(parent);
    other[0]->setClick(false);
    other[0]->move(100,230);
    other[0]->hide();

    other[1] = new Card(parent);
    other[1]->setClick(false);
    other[1]->move(500,50);
    other[1]->hide();

    other[2] = new Card(parent);
    other[2]->setClick(false);
    other[2]->move(1000,230);
    other[2]->hide();

    QFont font;
    font.setPointSize(14);
    status = new QLabel(parent);
    status->setGeometry(500,250,300,100);
    status->setFont(font);
    status->hide();
}

void GameStage::show_everything(int* arr)
{
    int i;
    for (i = 0; i < 13; i++) {
        card[i]->setImage(arr[i]);
        card[i]->show();
    }
}

void GameStage::setsocket(int sock)
{
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

void GameStage::show_others(int otherID,int index)
{
    if (index != -1) {
        if (index == 0) {
            other[1]->hide();
            other[2]->hide();
        }
        other[index]->setImage(otherID);
        other[index]->show();
    }
}

void GameStage::your_turn(bool flag)
{
    if (flag) {
        status->setStyleSheet("QLabel {color:green}");
        status->setText("Your Turn");
    } else {
        status->setStyleSheet("QLabel {}");
        status->setText("Wait for others");
    }
}

void GameStage::game_start(void)
{
    status->setStyleSheet("QLabel {}");
    status->setText("Wait others to join");
    status->show();
    thread->start();
}

void GameStage::hide_everything(int result)
{
    int i;
    status->hide();
    for (i = 0;i < 3;i++) {
        other[i]->hide();
    }
    emit goto_final(result);
}
