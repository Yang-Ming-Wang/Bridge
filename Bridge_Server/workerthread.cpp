#include "workerthread.h"

Userlist WorkerThread::userlist;
Table WorkerThread::table;
int WorkerThread::ID;
QMutex mutex;
QWaitCondition cond;

WorkerThread::WorkerThread(int id,int sock)
{
    clientId = id;
    sockfd = sock;
}

bool WorkerThread::recv_client_account(void)
{
    int isreg,result;
    char account[15],password[15];

    do {
        read(sockfd,&isreg,sizeof(int));

        if (isreg == -1) {
            return false;
        }

        read(sockfd,account,15);
        printf("your account [%s]\n",account);

        read(sockfd,password,15);
        printf("your password [%s]\n",password);

        if (isreg == 1) {
            printf("registor:\n");
            result = userlist.regist(account,password);
            if (result == 1) {
                printf("registor success\n");
            } else if (result == 2) {
                printf("can't create existing account\n");
            }
        } else {
            printf("login:\n");
            result = userlist.login(account,password);
            if (result == 1) {
                printf("login success\n");
            } else if (result == 2) {
                printf("account not exist\n");
            } else if (result == 3) {
                printf("incorrct password\n");
            }
        }
        write(sockfd,&result,sizeof(int));
    } while (isreg == 1 || result != 1);

    return true;
}

void WorkerThread::run(void)
{
    int state = -1;
    int card[13];
    while(1) {
        if (state == -1 && !recv_client_account()) {
            printf("client closed\n");
            close(sockfd);
            return ;
        }

        read(sockfd,&state,sizeof(int));

        if (state == 0) {
            //logout
            state = -1;
        } else if (state == 1){
            printf("User [%d] a game\n",clientId);
            table.addtable(clientId);
            printf("client [%d] add table\n",clientId);
            table.gettable(clientId,card);
            printf("client [%d] get table\n",clientId);
            write(sockfd,card,sizeof(int) * 13);

            deal_card();

            table.leavetable(clientId);

            state = 0;
        }
    }
}

void WorkerThread::deal_card(void)
{
    int i,j,order;

    for (i = 0;i < 13;i++) {
        order = table.getOrder(clientId);
        write(sockfd,&order,sizeof(int));

        for (j = 0;j < 4;j++) {
            if (j == order) {
                //read client ID then give other worker
                read(sockfd,&ID,sizeof(int));
                table.receive_card(ID);

                mutex.lock();
                cond.wakeAll();
                mutex.unlock();

            } else {
                //wait other order 0 worker read and write to client
                mutex.lock();
                cond.wait(&mutex);
                mutex.unlock();

                printf("clientiD %d release lock and send %d\n",clientId,ID);
                write(sockfd,&ID,sizeof(int));
            }
        }
        table.setOrder(i);
    }

    i = table.final_result(clientId);
    write(sockfd,&i,sizeof(int));

    return ;
}
