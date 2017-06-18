#ifndef USERLIST_H
#define USERLIST_H

#include <QtSql>
#include <QMap>
#include <QMutex>

typedef struct _clientData {
   int win,lose;
} clientData;

class Userlist
{
public:
    Userlist();
    int login(char *,char *);
    int regist(char *,char *);
    void logout(char *);
    int getLoginNum(void);
private:
    QSqlDatabase db;
    QMap<QString,clientData> map;
    QMutex mutex;
    int loginnum;
};

#endif // USERLIST_H
