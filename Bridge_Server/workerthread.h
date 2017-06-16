#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QTime>
#include <QMutex>
#include <QWaitCondition>
#include <unistd.h>
#include <arpa/inet.h>
#include "userlist.h"
#include "table.h"

class WorkerThread : public QThread
{
public:
    WorkerThread(int,int);
protected:
    void run(void);
private:
    void recv_client_account(void);
    void deal_card(void);
    static Userlist userlist;
    static Table table;
    static int ID;
    int sockfd,clientId;
    char nowaccount[15];
};

#endif // WORKERTHREAD_H
