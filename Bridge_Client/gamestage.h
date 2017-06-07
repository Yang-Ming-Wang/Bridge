#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <unistd.h>
#include <arpa/inet.h>

class GameStage : public QWidget
{
    Q_OBJECT
public:
    explicit GameStage(QWidget *parent = nullptr);
    void setsocket(int);

public slots:
    void show_everything(void);
private:
    QLabel *label[13];
    int sockfd;
};

#endif // GAMESTAGE_H
