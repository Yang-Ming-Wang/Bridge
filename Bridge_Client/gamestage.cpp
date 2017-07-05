#include "gamestage.h"

GameStage::GameStage(QWidget *parent) : QWidget(parent)
{
    int i;
    for (i = 0; i < 13; i++) {
        card[i] = new Card(this,i);
        card[i]->move(100 + 75*i,500);

        connect(card[i],SIGNAL(selected_card(int,int)),this,SLOT(send_card(int,int)));
    }

    other[0] = new Card(this);
    other[0]->setClick(false);
    other[0]->move(100,230);
    other[0]->hide();

    other[1] = new Card(this);
    other[1]->setClick(false);
    other[1]->move(500,50);
    other[1]->hide();

    other[2] = new Card(this);
    other[2]->setClick(false);
    other[2]->move(1000,230);
    other[2]->hide();

    QFont font;
    font.setPointSize(14);
    status = new QLabel(this);
    status->setGeometry(500,250,300,100);
    status->setFont(font);
}

void GameStage::setThread(ClientThread *t)
{
    thread = t;
}

void GameStage::show_everything(int* arr)
{
    int i;
    for (i = 0; i < 13; i++) {
        card[i]->setImage(arr[i]);
        card[i]->show();
    }
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

void GameStage::hide_everything(int result)
{
    int i;
    for (i = 0;i < 3;i++) {
        other[i]->hide();
    }
    emit stage_change(result);
}
