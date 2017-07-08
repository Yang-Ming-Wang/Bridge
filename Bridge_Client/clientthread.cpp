#include "clientthread.h"


ClientThread::ClientThread(QObject* parent): QThread(parent)
{

}

void ClientThread::run(void)
{
    int i,j,myorder,index;
    //inital get 13 random card
    int arr[13];
    read(sockfd,arr,sizeof(int) * 13);
    emit game_start(arr);

    //need to get turn to decide play card or not
    for (i = 0;i < 13;i++) {
        read(sockfd,&myorder,sizeof(int));
        index = 0;
        for (j = 0;j < 4;j++) {
            if (j == myorder) {
                isMyturn = true;
                emit your_turn(isMyturn);

                mutex.lock();
                ready.wait(&mutex);
                mutex.unlock();

                qInfo("you select [\033[31m%d\033[0m]",cardID);
                emit getcard(cardID,-1);

                write(sockfd,&cardID,sizeof(int));

            } else {
                isMyturn = false;
                emit your_turn(isMyturn);

                qInfo("\033[31m wait for read \033[0m");
                read(sockfd,&otherID,sizeof(int));
                qInfo("recv card[\033[31m%d\033[0m]",otherID);

                emit getcard(otherID,index);
                index++;
            }
        }
    }
    read(sockfd,&i,sizeof(int));
    if (i == 1) {
        emit result(4);
    } else {
        emit result(5);
    }
}

bool ClientThread::connectIP(QString str)
{
    struct sockaddr_in servaddr;
    char *connect_ip = str.toLatin1().data();

    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 ) {
        printf("socket error\n");
        return false;
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9877);

    if (inet_pton(AF_INET,connect_ip,&servaddr.sin_addr) <= 0) {
        printf("inet_ption error for %s\n",connect_ip);
    }

    if (::connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) {
        printf("connect error\n");
        return false;
    }
    return true;
}

int ClientThread::send_account(int isreg,const char *account,const char *password)
{
    char buffer[15];
    int success;

    if (sockfd >= 0) {
        write(sockfd,&isreg,sizeof(int));

        bzero(buffer,15);
        strcpy(buffer,account);
        write(sockfd,buffer,15);

        bzero(buffer,15);
        strcpy(buffer,password);
        write(sockfd,buffer,15);

        read(sockfd,&success,sizeof(int));
        return success;
    }
    return -1;
}

void ClientThread::send_quit(void)
{
    int state = -1;
    write(sockfd,&state,sizeof(int));
    ::close(sockfd);
}
void ClientThread::logout(void)
{
    int state = 0;
    write(sockfd,&state,sizeof(int));
}

void ClientThread::join_game(void)
{
    int state = 1;
    write(sockfd,&state,sizeof(int));
}

int ClientThread::refresh_data(char (*account)[15],int *win,int *lose)
{
    int i,loginnum,state = 2;

    write(sockfd,&state,sizeof(int));
    read(sockfd,&loginnum,sizeof(int));

    for (i = 0;i < loginnum;i++) {
        read(sockfd,account[i],sizeof(char) * 15);
        read(sockfd,&win[i],sizeof(int));
        read(sockfd,&lose[i],sizeof(int));
    }

    return loginnum;
}

void ClientThread::setsocket(int sock)
{
    sockfd = sock;
}

bool ClientThread::notify(int ID)
{
    bool card_selected = false;

    mutex.lock();
    if (isMyturn) {
        card_selected = true;
        cardID = ID;
        ready.wakeAll();
    }
    mutex.unlock();

    return card_selected;
}
