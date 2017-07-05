#ifndef WAITINGSCREEN_H
#define WAITINGSCREEN_H

#include <QWidget>
#include <QMovie>
#include <QLabel>

class WaitingScreen : public QWidget
{
    Q_OBJECT
public:
    explicit WaitingScreen(QWidget *parent = nullptr);

signals:

public slots:

private:
    QMovie *movie;
    QLabel *processLabel,*textlabel;
};

#endif // WAITINGSCREEN_H
