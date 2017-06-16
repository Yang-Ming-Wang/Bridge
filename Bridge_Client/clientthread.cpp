#include "clientthread.h"


ClientThread::ClientThread(QObject* parent,QMutex* mut,QWaitCondition* cond): QThread(parent)
{
    mutex = mut;
    ready = cond;
}

void ClientThread::run(void)
{
    int i;
    //inital get 13 random card
    //read(sockfd,arr,sizeof(int) * 13);

    //need to get turn to decide play card or not
    read(sockfd,&turn,sizeof(int));
    qInfo("TURN::[%d]",turn);
    for (i = 0;i < 4;i++) {
        if (turn == 0) {
            qInfo("\033[31m your turn\033[0m");

            mutex->lock();
            ready->wait(mutex);
            mutex->unlock();

            qInfo("you select [\033[31m%d\033[0m]",cardID);

            write(sockfd,&cardID,sizeof(int));

        } else {
            qInfo("\033[31m wait for read \033[0m");
            read(sockfd,&otherID,sizeof(int));
            qInfo("recv card[\033[31m%d\033[0m]",otherID);
            emit getcard(otherID);
        }
        turn--;
    }
    qInfo("thread leave a loop");
}

void ClientThread::setsocket(int sock)
{
    sockfd = sock;
}

bool ClientThread::notify(int ID)
{
    bool card_selected = false;

    mutex->lock();
    if (turn == 0) {
        card_selected = true;
        cardID = ID;
        ready->wakeAll();
    }
    mutex->unlock();

    return card_selected;
}
