#include "gamestage.h"

GameStage::GameStage(QWidget *parent) : QWidget(parent)
{
    QImage img("king-spades.png");
    int i;
    for (i = 0; i < 13; i++) {
        label[i] = new QLabel(parent);
        label[i]->setText("test");
        label[i]->setPixmap(QPixmap::fromImage(img));
        label[i]->setScaledContents(true);
        label[i]->setGeometry(0 + 150*i,0,150,100);
        label[i]->hide();
    }
}

void GameStage::show_everything(void)
{
    int i;
    for (i = 0; i < 13; i++) {
        label[i]->show();
    }
}
