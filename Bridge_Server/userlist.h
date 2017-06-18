#ifndef USERLIST_H
#define USERLIST_H

#include <QtSql>

class Userlist
{
public:
    Userlist();
    int login(char *,char *);
    int regist(char *,char *);
private:
    QSqlDatabase db;
    void readuserfile(void);
    int loginnum;
    int usernum;
};

#endif // USERLIST_H
