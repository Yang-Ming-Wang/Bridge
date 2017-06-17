#ifndef SERVER_H
#define SERVER_H

#include <QList>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include "workerthread.h"

#define NUMCLIENT 8

class Server
{
public:
    Server();
private:
    int prepare_server();
    QList<WorkerThread*> worker;
};

#endif // SERVER_H
