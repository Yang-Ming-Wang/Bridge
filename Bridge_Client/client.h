#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include "login.h"
#include "lobby.h"
#include "gamestage.h"
#include "finalscreen.h"

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = nullptr);
    bool connectIP(QString str);
    ~Client();

public slots:
    void ChangeState(void);
private:
    Login *login;
    Lobby *lobby;
    GameStage *game;
    FinalScreen *final;
    QStackedWidget *stack;
    QVBoxLayout *mainlayout;
};

#endif // CLIENT_H
