#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "subscriber.h"

class Lobby : public Subscriber
{
    Q_OBJECT
public:
    explicit Lobby(QWidget *parent = nullptr);

signals:
    void stage_change(int);

public slots:
    void refresh_data(void);
private slots:
    void logout_from_server(void);
    void join_game(void);

private:
    QLabel *label;
    QLabel *user[8];
    QPushButton *logout,*join,*refresh;
};

#endif // LOBBY_H
