#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <QWidget>
#include <QLabel>
#include <unistd.h>
#include <arpa/inet.h>
#include "card.h"
#include "clientthread.h"

class GameStage : public QWidget
{
    Q_OBJECT
public:
    explicit GameStage(QWidget *parent = nullptr);
    void setsocket(int);

public slots:
    void show_everything(void);
    void show_others(int,int);
    void your_turn(bool);
private slots:
    void send_card(int,int);
private:
    Card *card[13];
    Card *other[3];
    ClientThread *thread;
    QLabel *status;
    int sockfd;
};

#endif // GAMESTAGE_H
