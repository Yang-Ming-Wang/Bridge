#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

class Server
{
public:
    Server();
private:
    int prepare_server();
};

#endif // SERVER_H
