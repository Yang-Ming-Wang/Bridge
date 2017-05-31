#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <unistd.h>
#include <QVector>

class WorkerThread : public QThread
{
public:
    WorkerThread(int);
protected:
    void run(void);
private:
    void recv_client_account(void);
    int login(char *,char *);
    int regist(char *,char *);
    void readuserfile(void);
    void writeuserfile(void);
    int sockfd;
    static QVector<QString> validaccount;
    static QVector<QString> validpassword;
    static int usernum;
};

#endif // WORKERTHREAD_H
