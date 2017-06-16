#include "clientthread.h"


ClientThread::ClientThread(QObject* parent,QMutex* mut,QWaitCondition* cond): QThread(parent)
{
    card_selected = false;
    mutex = mut;
    ready = cond;
}

void ClientThread::run(void)
{
    int i,turn;
    //inital get 13 random card
    //read(sockfd,arr,sizeof(int) * 13);

    //need to get turn to decide play card or not
    turn = 0;
    for (i = 0;i < 4;i++) {
        if (turn == 0) {
            mutex->lock();
            if (!card_selected) {
                ready->wait(mutex);
            }
            mutex->unlock();

            qInfo("\033[31myou select [%d]\033[0m",cardID);
            card_selected = false;

            //write(sockfd,&cardID,sizeof(int));

            //for testing
            otherID = cardID;
            emit getcard(otherID);
        } else {
            //read(sockfd,&otherID,sizeof(int));
            //emit getcard(otherID);
        }
        //turn--;
    }
    qInfo("thread leave a loop");
}

void ClientThread::setsocket(int sock)
{
    sockfd = sock;
}

void ClientThread::notify(int ID)
{
    mutex->lock();

    card_selected = true;
    cardID = ID;
    ready->wakeAll();

    mutex->unlock();
}
