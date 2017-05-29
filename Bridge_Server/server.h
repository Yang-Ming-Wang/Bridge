#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include "workerthread.h"

class Server
{
public:
    Server();
private:
    int prepare_server();
    WorkerThread *worker[4];
};

#endif // SERVER_H
