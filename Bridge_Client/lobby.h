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
    void get_online_info(void);

signals:
    void stage_change(int);

private slots:
    void logout_from_server(void);
    void join_game(void);
    void refresh_data(void);

private:
    int sockfd;
    QLabel *label;
    QLabel *user[8];
    QPushButton *logout,*join,*refresh;
};

#endif // LOBBY_H
