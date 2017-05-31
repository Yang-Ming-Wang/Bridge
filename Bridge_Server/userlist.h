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
private:
    QVector<QString> validaccount;
    QVector<QString> validpassword;
    QMutex mutex;
    void readuserfile(void);
    int usernum;
};

#endif // USERLIST_H
