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
}

void Card::mousePressEvent(QMouseEvent*)
{
    emit selected_card(cardID,index);
}

void Card::enterEvent(QEvent*)
{
    //use green color: #3d917f
    label->setStyleSheet("QLabel {border: 5px solid #3d917f}");
}
void Card::leaveEvent(QEvent*)
{
    label->setStyleSheet("QLabel {border:none}");
}

void Card::setImage(int id)
{
    QImage img("poker/" + QString::number(id) + ".jpg");
    label->setPixmap(QPixmap::fromImage(img));
    cardID = id;
}
