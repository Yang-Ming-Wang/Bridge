#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <unistd.h>

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(QObject*,QMutex*,QWaitCondition*);
    void setsocket(int);
    void notify(int);
protected:
    void run(void);
private:
    int sockfd,cardID;
    int otherID;
    bool card_selected;
    QMutex *mutex;
    QWaitCondition *ready;
signals:
    void getcard(int);
};

#endif // CLIENTTHREAD_H
