#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "login.h"
#include "lobby.h"
#include "gamestage.h"
#include "finalscreen.h"
#include "clientthread.h"
#include "waitingscreen.h"

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    bool connectIP(QString str);
    ~Client();

public slots:
    void ChangeState(int);
private:
    Login *login;
    Lobby *lobby;
    GameStage *game;
    FinalScreen *final;
    ClientThread *thread;
    WaitingScreen *waitscreen;
    QStackedWidget *stack;
    QVBoxLayout *mainlayout;
};

#endif // CLIENT_H
