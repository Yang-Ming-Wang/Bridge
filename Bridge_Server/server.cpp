#include "server.h"

Server::Server()
{
    int id,listenfd,socket,clients;
    struct sockaddr_in recvaddr;
    socklen_t recv;

    listenfd = prepare_server();

    recv = sizeof(recvaddr);
    printf("Server Activated!!\n");

    //Use inifinit loop to prevent Server from terminate.
    id = 0;
    clients = 0;
    while(1) {
        if (clients < NUMCLIENT) {
            do socket = accept(listenfd,(struct sockaddr*)&recvaddr,&recv);
            while (socket < 0 && errno == EINTR);

            worker.append(new WorkerThread(id,socket));
            worker.last()->start();
            clients++;

            QList<WorkerThread*>::iterator element;
            for (element = worker.begin();element != worker.end();element++) {
                if ((*element)->isFinished()) {
                    worker.erase(element);
                    clients--;
                }
            }
        }

        id++;
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
