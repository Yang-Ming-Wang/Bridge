#include "card.h"

Card::Card(QWidget *parent) : QWidget(parent)
{
    resize(150,100);
    label = new QLabel(this);
    label->setScaledContents(true);
    label->resize(150,100);
    cardID = 0;
}

void Card::mousePressEvent(QMouseEvent*) {
    emit selected_card(cardID);
}

void Card::setImage(int id)
{
    QImage img("poker/" + QString::number(id) + ".jpg");
    label->setPixmap(QPixmap::fromImage(img));
    cardID = id;
}
