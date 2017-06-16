#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <QWidget>
#include <QLabel>
#include <QImage>
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
    void show_others(int);
private slots:
    void send_card(int,int);
private:
    Card *card[13];
    Card *other;
    ClientThread *thread;
    int sockfd;
};

#endif // GAMESTAGE_H
