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

public slots:
    void show_everything(void);

private:
    void hide_everything(void);
    QLabel *label;
};

#endif // LOBBY_H
