#include "workerthread.h"

Userlist WorkerThread::userlist;

WorkerThread::WorkerThread(int sock)
{
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
    do {
        recv_client_account();
        read(sockfd,&state,sizeof(int));
        if (state == 0) {
            userlist.logoutuser(nowaccount);
            bzero(nowaccount,15);
        } else if (state == 1){
            printf("User play a game\n");
        }
    } while (state == 0);
}
