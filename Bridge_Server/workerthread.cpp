#include "workerthread.h"

int WorkerThread::usernum = 0;
QVector<QString> WorkerThread::validaccount;
QVector<QString> WorkerThread::validpassword;

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

        readuserfile();

        printf("your account [%s]\n",account);

        read(sockfd,password,15);
        printf("your password [%s]\n",password);

        if (isreg == 1) {
            printf("registor\n");
            if (regist(account,password) == 0) {
                printf("success\n");
            } else {
                printf("fail\n");
            }

        } else {
            printf("login\n");
            result = login(account,password);
        }
        //for test purpose.
        //result = 1;
        write(sockfd,&result,sizeof(int));
    } while (isreg == 1 || result != 1);
    writeuserfile();
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

int WorkerThread::login(char *account,char *password)
{
    int result = 0,registed = 0;
    for (int i = 0;i < usernum;i ++) {
        if (validaccount[i] == account) {
            registed = 1;
            if (validpassword[i] == password) {
                    printf("login success\n");
                    result = 1;
            } else {
                printf("incorrct password\n");
                result = 3;
            }
            break;
        }
    }
    if (registed != 1){
        printf("incorrect account\n");
        result = 2;
    }
    return result;
}

int WorkerThread::regist(char *account,char *password)
{
    int registed = 0;
    for (int i = 0;i < usernum;i ++) {
        if (validaccount[i] == account) {
            printf("account existed\n");
            registed = 1;
            break;
        }
    }
    if (registed != 1){
        validaccount.push_back(account);
        validpassword.push_back(password);
        usernum ++;
    }
    return registed;
}

void WorkerThread::writeuserfile(void){
    FILE *userfile;
    userfile = fopen("userlist","w");
    for (int i = 0;i < usernum;i ++) {
        fprintf(userfile,"%s %s\n",validaccount[i].toStdString().c_str(),validpassword[i].toStdString().c_str());
    }
    fclose(userfile);
}

void WorkerThread::readuserfile(void){
    FILE *userfile;
    char tempaccount[15],temppassword[15];
    userfile = fopen("userlist","r");
    while (fscanf(userfile,"%s %s",tempaccount,temppassword) != EOF) {
        validaccount.push_back(tempaccount);
        validpassword.push_back(temppassword);
        usernum ++;
    }
    fclose(userfile);
}
