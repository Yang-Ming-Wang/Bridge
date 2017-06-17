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
        qInfo("win the game");
    } else {
        qInfo("lose the game");
    }
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
