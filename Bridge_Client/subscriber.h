#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QWidget>
#include "clientthread.h"

class Subscriber : public QWidget
{
public:
    explicit Subscriber(QWidget *parent = nullptr);
    void attach(ClientThread*);
protected:
    ClientThread *thread;
};

#endif // SUBSCRIBER_H
