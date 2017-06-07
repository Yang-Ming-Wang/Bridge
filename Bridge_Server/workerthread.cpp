#include "workerthread.h"

Userlist WorkerThread::userlist;

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

void WorkerThread::shuffle(int *arr)
{
    int i,temp,index;
    qsrand(QTime::currentTime().msec());
    for (i = 0; i < 52; i++) {
        arr[i] = i;
    }
    for (i = 52; i > 0; i--) {
        index = qrand() % i;
        temp = arr[index];
        arr[index] = arr[i - 1];
        arr[i - 1] = temp;
    }
}

void WorkerThread::run(void)
{
    int state,random[52];
    do {
        recv_client_account();
        read(sockfd,&state,sizeof(int));
        if (state == 0) {
            userlist.logoutuser(nowaccount);
            bzero(nowaccount,15);
        } else if (state == 1){
            printf("User play a game\n");
            /* Modify here !!
             *
             * In here, you need to divid array 'random' into four part
             * , each part will send to diffierent client.The variable
             * 'clientID' may help you to do this.
             * Further, the array must be *static* and use my function
             * 'shuffle' to initial it.
             */
            shuffle(random);
            for (int i = 0; i < 52;i++) {
                printf("%d\n",random[i]);
            }
            write(sockfd,random,sizeof(int) * 13);
        }
    } while (state == 0);
}
