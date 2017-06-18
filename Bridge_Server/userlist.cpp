#include "userlist.h"

Userlist::Userlist()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("Server");
    db.setDatabaseName("ClientData.db");
    db.setUserName("admin");
    db.setPassword("admin");

    db.open();

    QSqlQuery query;
    if (!db.tables().contains("Users")) {
        query.exec("CREATE TABLE Users ("
                   "account varchar(15) PRIMARY KEY, "
                   "password varcahr(15),"
                   "numOfwins INTEGER DEFAULT 0,"
                   "numOflose INTEGER DEFAULT 0)");
    }

    loginnum = 0;
}

int Userlist::login(char *account,char *password)
{
    QSqlQuery query;
    clientData data;
    int result;
    query.prepare("SELECT password,numOfwins,numOflose FROM Users WHERE account=:account");
    query.bindValue(":account",account);
    query.exec();
    if (query.next()) {
        if (query.value(0).toString() == password) {
            data.win = query.value(1).toInt();
            data.lose = query.value(2).toInt();
            mutex.lock();
            if (!map.contains(QString(account))) {
                map[QString(account)] = data;
                loginnum++;
                result  = 1;
            } else {
                result = 4;
            }
            mutex.unlock();
        } else {
            result =  3;
        }
    } else {
        result = 2;
    }
    return result;
}

int Userlist::regist(char *account,char *password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Users (account,password) "
                  "VALUES (:account, :password)");
    query.bindValue(":account", account);
    query.bindValue(":password", password);
    if (query.exec()) {
        return 1;
    }
    return 2;
}

void Userlist::logout(char *account)
{
    mutex.lock();
    map.remove(QString(account));
    loginnum --;
    mutex.unlock();
}
