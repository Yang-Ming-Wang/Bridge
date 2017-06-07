#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QTime>
#include <unistd.h>
#include <arpa/inet.h>
#include "userlist.h"

class WorkerThread : public QThread
{
public:
    WorkerThread(int,int);
protected:
    void run(void);
private:
    void recv_client_account(void);
    void shuffle(int* );
    static Userlist userlist;
    int sockfd,clientId;
    char nowaccount[15];
};

#endif // WORKERTHREAD_H
