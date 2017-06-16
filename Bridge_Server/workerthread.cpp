#include "workerthread.h"

Userlist WorkerThread::userlist;
Table WorkerThread::table;
int WorkerThread::ID[4];
QMutex WorkerThread::mutex;
QWaitCondition WorkerThread::cond;

WorkerThread::WorkerThread(int id,int sock)
{
    clientId = id;
    sockfd = sock;
}

void WorkerThread::recv_client_account(void)
{
    int isreg,result;
    char account[15],password[15];

    do {
        read(sockfd,&isreg,sizeof(int));

        read(sockfd,account,15);
        printf("your account [%s]\n",account);

        read(sockfd,password,15);
        printf("your password [%s]\n",password);

        if (isreg == 1) {
            printf("registor ");
            result = userlist.regist(account,password);
            if (result == 1) {
                printf("success\n");
            } else {
                printf("fail\n");
            }
        } else {
            printf("login\n");
            result = userlist.login(account,password);
            if (result == 1) {
                userlist.loginuser(account);
                strcpy(nowaccount,account);
            }
        }
        write(sockfd,&result,sizeof(int));
    } while (isreg == 1 || result != 1);

    userlist.writeuserfile();
}

void WorkerThread::run(void)
{
    int state;
    int card[13];
    do {
        recv_client_account();
        read(sockfd,&state,sizeof(int));
        if (state == 0) {
            userlist.logoutuser(nowaccount);
            bzero(nowaccount,15);
        } else if (state == 1){
            printf("User [%d] a game\n",clientId);
            table.addtable(clientId);
            printf("client [%d] add table\n",clientId);
            table.gettable(clientId,card);
            printf("client [%d] get table\n",clientId);
            write(sockfd,card,sizeof(int) * 13);

            deal_card();

        }
    } while (state == 0);
}

void WorkerThread::deal_card(void)
{
    int i,order;
    int color,diff,winner,max;

    //for test
    order = clientId % 4;
    write(sockfd,&order,sizeof(int));

    for (i = 0;i < 4;i++) {
        if (order == 0) {
            //read client ID then give other worker
            read(sockfd,&ID[i],sizeof(int));
            printf("clientID %d recv Card = %d\n",clientId,ID[i]);

            mutex.lock();
            cond.wakeAll();
            mutex.unlock();

        } else {
            //wait other order 0 worker read and write to client
            mutex.lock();
            cond.wait(&mutex);
            mutex.unlock();

            printf("clientiD %d release lock and send %d\n",clientId,ID[i]);
            write(sockfd,&ID[i],sizeof(int));
        }
        order--;
    }

    color = ID[0]/13*13;
    max = 0;
    for (i = 0;i < 4;i++) {
        diff = ID[i] - color;
        if (diff < 13 && diff > max) {
            max = diff;
            winner = i;
        }
    }
    printf("winner [%d] use card [%d] to win!!\n",winner,ID[winner]);

    return ;
}
