#include "userlist.h"

Userlist::Userlist()
{
    usernum = 0;
    loginnum = 0;
    readuserfile();
}

int Userlist::login(char *account,char *password)
{
    for (int i = 0;i < usernum;i ++) {
        if (validaccount[i] == account) {
            if (validpassword[i] == password) {
                printf("login success\n");
                return 1;
            } else {
                printf("incorrct password\n");
                return 3;
            }
        }
    }
    printf("incorrect account\n");
    return 2;
}

int Userlist::regist(char *account,char *password)
{
    for (int i = 0;i < usernum;i ++) {
        if (validaccount[i] == account) {
            printf("account existed\n");
            return 2;
        }
    }

    mutex.lock();
    validaccount.push_back(account);
    validpassword.push_back(password);
    usernum ++;
    mutex.unlock();

    return 1;
}

void Userlist::writeuserfile(void)
{
    FILE *userfile;

    mutex.lock();
    userfile = fopen("userlist","w");
    for (int i = 0;i < usernum;i ++) {
        fprintf(userfile,"%s %s\n",validaccount[i].toStdString().c_str(),validpassword[i].toStdString().c_str());
    }
    fclose(userfile);
    mutex.unlock();
}

void Userlist::readuserfile(void)
{
    FILE *userfile;
    char tempaccount[15],temppassword[15];
    userfile = fopen("userlist","r");
    if (userfile == NULL) {
        userfile = fopen("userlist","w");
    }
    while (fscanf(userfile,"%s %s",tempaccount,temppassword) != EOF) {
        validaccount.push_back(tempaccount);
        validpassword.push_back(temppassword);
        usernum ++;
    }
    fclose(userfile);
}

void Userlist::loginuser(char *account)
{
    mutex.lock();
    loginnum ++;
    loginlist.push_back(account);
    mutex.unlock();
    for (int i = 0;i < loginnum;i ++) {
        printf("Account [%s] online\n",loginlist[i].toStdString().c_str());
    }
}

void Userlist::logoutuser(char *account)
{
    for (int i = 0;i < loginnum;i ++) {
        if (loginlist[i] == account) {
            printf("Account [%s] logout\n",account);
            mutex.lock();
            loginlist.remove(i);
            loginnum --;
            mutex.unlock();
            return ;
        }
    }
    printf("logout user not found\n");
}
