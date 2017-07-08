#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <QWidget>
#include <QLabel>
#include "card.h"
#include "clientthread.h"
#include "subscriber.h"

class GameStage : public Subscriber
{
    Q_OBJECT
public:
    explicit GameStage(QWidget *parent = nullptr);

signals:
    void stage_change(int);
public slots:
    void show_everything(int*);
    void hide_everything(int);
    void show_others(int,int);
    void your_turn(bool);
private slots:
    void send_card(int,int);
private:
    Card *card[13];
    Card *other[3];
    QLabel *status;
};

#endif // GAMESTAGE_H
