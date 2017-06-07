#include "server.h"

Server::Server()
{
    int i,listenfd,socket;
    struct sockaddr_in recvaddr;
    socklen_t recv;

    listenfd = prepare_server();

    recv = sizeof(recvaddr);
    printf("Server Activated!!\n");

    for (i = 0;i < 4;i++) {
        do socket = accept(listenfd,(struct sockaddr*)&recvaddr,&recv);
        while (socket < 0 && errno == EINTR);

        worker[i] = new WorkerThread(i,socket);
        worker[i]->start();
    }
}

int Server::prepare_server()
{
    int listenfd;
    struct sockaddr_in servaddr;

    listenfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9877);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    listen(listenfd,1024);

    return listenfd;
}
