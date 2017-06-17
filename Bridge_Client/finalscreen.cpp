#include "finalscreen.h"

FinalScreen::FinalScreen(QWidget *parent) : QWidget(parent)
{
    back = new QPushButton(parent);
    //connect()

    QFont font;
    font.setPointSize(14);

    label = new QLabel(parent);
    label->setGeometry(200,300,300,100);
    label->setFont(font);

    hide_everything();
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
