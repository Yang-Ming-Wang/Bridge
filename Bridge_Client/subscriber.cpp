#include "subscriber.h"

Subscriber::Subscriber(QWidget *parent): QWidget(parent)
{

}

void Subscriber::attach(ClientThread *t)
{
    thread = t;
}
