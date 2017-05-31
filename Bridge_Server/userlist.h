#ifndef USERLIST_H
#define USERLIST_H

#include <QVector>
#include <QMutex>

class Userlist
{
public:
    Userlist();
    int login(char *,char *);
    int regist(char *,char *);
    void writeuserfile(void);
    void loginuser(char *);
    void logoutuser(char *);
private:
    QVector<QString> validaccount;
    QVector<QString> validpassword;
    QVector<QString> loginlist;
    QMutex mutex;
    void readuserfile(void);
    int loginnum;
    int usernum;
};

#endif // USERLIST_H
