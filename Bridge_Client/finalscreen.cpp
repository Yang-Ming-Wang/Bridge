#include "finalscreen.h"

FinalScreen::FinalScreen(QWidget *parent) : QWidget(parent)
{
    back = new QPushButton("Back",this);
    back->setGeometry(500,500,200,100);
    connect(back,SIGNAL(clicked()),this,SLOT(back_to_lobby()));

    QFont font;
    font.setPointSize(14);

    label = new QLabel(this);
    label->setGeometry(250,50,800,400);
    label->setScaledContents(true);
    label->setFont(font);
}

void FinalScreen::setWinner(int win)
{
    QImage img;
    if (win == 1) {
        img.load("image/winner.jpg");
    } else {
        img.load("image/loser.jpg");
    }
    label->setPixmap(QPixmap::fromImage(img));
}

void FinalScreen::back_to_lobby(void)
{
    emit stage_change(1);
}
