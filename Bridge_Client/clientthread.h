#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <arpa/inet.h>
#include <unistd.h>

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(QObject*);
    void setsocket(int);
    bool notify(int);
    bool connectIP(QString str);
    int send_account(int,const char*,const char*);
    void send_quit(void);
    void logout(void);
    void join_game(void);
    int refresh_data(char (*)[15],int*,int*);
protected:
    void run(void);
private:
    int sockfd,cardID;
    int otherID;
    bool isMyturn;
    QMutex mutex;
    QWaitCondition ready;
signals:
    void getcard(int,int);
    void your_turn(bool);
    void game_start(int*);
    void stage_change(int);
    void result(int);
};

#endif // CLIENTTHREAD_H
