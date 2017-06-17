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
    label->setGeometry(500,300,300,100);
    label->setFont(font);
    label->hide();

}

void FinalScreen::show_everything(int win)
{
    if (win == 1) {
        label->setText("Win");
    } else {
        label->setText("Lose");
    }
    label->show();
    back->show();
}

void FinalScreen::hide_everything(void)
{
    label->hide();
    back->hide();

    emit back_to_lobby();
}
