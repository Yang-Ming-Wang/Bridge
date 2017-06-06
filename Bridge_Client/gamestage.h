#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class GameStage : public QWidget
{
    Q_OBJECT
public:
    explicit GameStage(QWidget *parent = nullptr);

public slots:
    void show_everything(void);
private:
    QLabel *label[13];
};

#endif // GAMESTAGE_H
