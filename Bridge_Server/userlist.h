#ifndef USERLIST_H
#define USERLIST_H

#include <QtSql>
#include <QMap>
#include <QMutex>
#include <unistd.h>

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
    void send_online_info(int);
    void write_result(char *,int);
private:
    clientData get_user_score(char *);
    QSqlDatabase db;
    QMap<QString,clientData> map;
    QMutex mutex;
    int loginnum;
};

#endif // USERLIST_H
