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

void WorkerThread::recv_client_account(void)
{
    int isreg,result;
    char password[15];

    read(sockfd,&isreg,sizeof(int));

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

        switch (result) {
        case 1:
            printf("login success\n");
            break;
        case 2:
            printf("account not exist\n");
            break;
        case 3:
            printf("incorrct password\n");
            break;
        case 4:
            printf("already login\n");
            break;
        }
    }
    write(sockfd,&result,sizeof(int));

}

void WorkerThread::run(void)
{
    int state,card[13];
    do {
        read(sockfd,&state,sizeof(int));

        switch (state) {
        case -1:
            printf("client closed\n");
            close(sockfd);
            break;
        case 0:
            userlist.logout(account);
            break;
        case 1:
            recv_client_account();
            break;
        case 2:
            printf("User [%d] a game\n",clientId);
            table.addtable(clientId);
            printf("client [%d] add table\n",clientId);
            table.gettable(clientId,card);
            printf("client [%d] get table\n",clientId);
            write(sockfd,card,sizeof(int) * 13);

            deal_card();

            table.leavetable(clientId);
            break;
        case 3:
            userlist.send_online_info(sockfd);
            break;
        }
    } while (state > -1);
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
    userlist.write_result(account,i);
    write(sockfd,&i,sizeof(int));

    return ;
}
