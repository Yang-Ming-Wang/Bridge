#include "workerthread.h"

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
            printf("registor\n");
        } else {
            printf("login\n");
        }
        //for test perpose.
        result = 1;
        write(sockfd,&result,sizeof(int));
    } while (isreg == 1 || result != 1);

}

void WorkerThread::run(void)
{
    recv_client_account();
    int logout;
    read(sockfd,&logout,sizeof(int));
    if (logout == 1) {
        printf("client logout\n");
    }
}
