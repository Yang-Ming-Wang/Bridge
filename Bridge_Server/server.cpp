#include "server.h"

void* worker(void *sock)
{
    int socket = *(int *)sock;
    char buf[256];
    //test socket

    int isreg;
    read(socket,&isreg,sizeof(int));
    if (isreg == 1) {
        printf("registor\n");
    } else {
        printf("login\n");
    }
    read(socket,buf,15);
    printf("your account [%s]\n",buf);

    read(socket,buf,15);
    printf("your password [%s]\n",buf);

    pthread_exit(NULL);
}

Server::Server()
{
    int i,listenfd,socket[4];
    pthread_t threads[4];
    struct sockaddr_in recvaddr;
    socklen_t recv;

    listenfd = prepare_server();

    recv = sizeof(recvaddr);
    printf("Hello world server\n");
    for (i = 0;i < 4;i++) {

        do socket[i] = accept(listenfd,(struct sockaddr*)&recvaddr,&recv);
        while (socket[i] < 0 && errno == EINTR);

        pthread_create(&threads[i],NULL,worker,(void*)&socket[i]);
        pthread_detach(threads[i]);
    }
    pthread_exit(NULL);
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
