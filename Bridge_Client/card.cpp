#include "card.h"

Card::Card(QWidget *parent,int idx) : QWidget(parent)
{
    resize(150,100);
    setAttribute(Qt::WA_Hover,true);
    label = new QLabel(this);
    label->setScaledContents(true);
    label->resize(150,100);
    cardID = 0;
    index = idx;
    setClick(true);
}

void Card::mousePressEvent(QMouseEvent*)
{
    if (clickable) {
        emit selected_card(cardID,index);
    }
}

void Card::enterEvent(QEvent*)
{
    if (clickable) {
        label->setStyleSheet("QLabel {border: 5px solid #3d917f}"); //green color
    }
}
void Card::leaveEvent(QEvent*)
{
    if (clickable) {
        label->setStyleSheet("QLabel {border:none}");
    }
}

void Card::setImage(int id)
{
    QImage img("poker/" + QString::number(id) + ".jpg");
    label->setPixmap(QPixmap::fromImage(img));
    cardID = id;
}

void Card::setClick(bool click)
{
    clickable = click;
}
