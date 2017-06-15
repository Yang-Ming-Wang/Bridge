#include "gamestage.h"

GameStage::GameStage(QWidget *parent) : QWidget(parent)
{
    int i;
    for (i = 0;i < 52;i++) {
        img[i] = new QImage("poker/" + QString::number(i) + ".jpg");
    }
    for (i = 0; i < 13; i++) {
        label[i] = new QLabel(parent);
        label[i]->setText("test");
        label[i]->setScaledContents(true);
        label[i]->setGeometry(100 + 75*i,500,150,100);
        label[i]->hide();
    }
}

void GameStage::show_everything(void)
{
    int i,arr[13];
    read(sockfd,arr,sizeof(int) * 13);
    for (i = 0; i < 13; i++) {
        label[i]->setPixmap(QPixmap::fromImage(*img[arr[i]]));
        label[i]->show();
        qDebug("%d",arr[i]);
    }
}

void GameStage::setsocket(int sock)
{
    sockfd = sock;
}
