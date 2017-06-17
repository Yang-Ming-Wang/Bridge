#include "finalscreen.h"

FinalScreen::FinalScreen(QWidget *parent) : QWidget(parent)
{
    back = new QPushButton("Back",parent);
    back->setGeometry(500,500,200,100);
    back->hide();
    connect(back,SIGNAL(clicked()),this,SLOT(hide_everything()));

    QFont font;
    font.setPointSize(14);

    label = new QLabel(parent);
    label->setGeometry(250,50,800,400);
    label->setScaledContents(true);
    label->setFont(font);
    label->hide();
}

void FinalScreen::show_everything(int win)
{
    QImage img;
    if (win == 1) {
        img.load("image/winner.jpg");
    } else {
        img.load("image/loser.jpg");
    }
    label->setPixmap(QPixmap::fromImage(img));
    label->show();
    back->show();
}

void FinalScreen::hide_everything(void)
{
    label->hide();
    back->hide();

    emit back_to_lobby();
}
