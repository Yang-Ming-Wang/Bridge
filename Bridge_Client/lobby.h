#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Lobby : public QWidget
{
    Q_OBJECT
public:
    explicit Lobby(QWidget *parent = nullptr);

signals:
    void go_back(void);

public slots:
    void show_everything(void);

private slots:
    void logout_from_server(void);

private:
    void hide_everything(void);
    QLabel *label;
    QPushButton *logout;
};

#endif // LOBBY_H
