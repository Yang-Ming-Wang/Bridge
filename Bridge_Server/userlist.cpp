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
    query.prepare("SELECT password FROM Users WHERE account=:account");
    query.bindValue(":account",account);
    query.exec();
    if (query.next()) {
        if (query.value(0).toString() == password) {
            data = get_user_score(account);
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

void Userlist::send_online_info(int sockfd)
{
    char account[15];
    write(sockfd,&loginnum,sizeof(int));
    QMap<QString, clientData>::iterator i;
    for (i = map.begin(); i != map.end(); i++) {
        strcpy(account,i.key().toLatin1().data());
        write(sockfd,account,sizeof(char) * 15);
    }
}

void Userlist::write_result(char *account, int result)
{
    QSqlQuery query;
    clientData data;
    data = get_user_score(account);

    if (result == 1) {
        data.win++;
    } else {
        data.lose++;
    }

    map[QString(account)] = data;

    query.prepare("UPDATE Users SET numOfwins =:win, numOflose =:lose WHERE account=:account");
    query.bindValue(":win",data.win);
    query.bindValue(":lose",data.lose);
    query.bindValue(":account",account);
    query.exec();
}
clientData Userlist::get_user_score(char *account)
{
    QSqlQuery query;
    clientData data;

    query.prepare("SELECT numOfwins,numOflose FROM Users WHERE account=:account");
    query.bindValue(":account",account);
    query.exec();

    query.next();
    data.win = query.value(0).toInt();
    data.lose = query.value(1).toInt();

    return data;
}
