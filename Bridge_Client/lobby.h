#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <unistd.h>

class Lobby : public QWidget
{
    Q_OBJECT
public:
    explicit Lobby(QWidget *parent = nullptr);
    void setsocket(int);

signals:
    void go_back(void);
    void play_game(void);

public slots:
    void show_everything(void);

private slots:
    void logout_from_server(void);
    void join_game(void);
    void get_online_info(void);

private:
    void hide_everything(void);
    int sockfd;
    QLabel *label;
    QPushButton *logout,*join,*refresh;
};

#endif // LOBBY_H
