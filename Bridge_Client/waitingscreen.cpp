#include "waitingscreen.h"

WaitingScreen::WaitingScreen(QWidget *parent) : QWidget(parent)
{
    //for test
    setFixedSize(1280,720);

    movie = new QMovie("loading.gif");
    processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    processLabel->setScaledContents(true);
    processLabel->setGeometry(480,450,300,30);
    movie->start();

    QFont font;
    font.setPointSize(14);
    textlabel = new QLabel(this);
    textlabel->setText("Wait others to join");
    textlabel->setGeometry(500,250,300,100);
    textlabel->setFont(font);
}
