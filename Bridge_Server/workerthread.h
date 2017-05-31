#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <unistd.h>
#include "userlist.h"

class WorkerThread : public QThread
{
public:
    WorkerThread(int);
protected:
    void run(void);
private:
    void recv_client_account(void);
    static Userlist userlist;
    int sockfd;
    char nowaccount[15];
};

#endif // WORKERTHREAD_H
