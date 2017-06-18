#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "lobby.h"
#include "gamestage.h"
#include "finalscreen.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool connectIP(QString str);
    ~MainWindow();

private:
    Login *login;
    Lobby *lobby;
    GameStage *game;
    FinalScreen *final;
};

#endif // MAINWINDOW_H
