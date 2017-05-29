#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <unistd.h>

class WorkerThread : public QThread
{
public:
    WorkerThread(int);
protected:
    void run(void);
private:
    void recv_client_account(void);
    int sockfd;
};

#endif // WORKERTHREAD_H
