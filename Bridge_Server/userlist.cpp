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
                   "password varcahr(15))");
    }

    usernum = 0;
    loginnum = 0;
}

int Userlist::login(char *account,char *password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM Users WHERE account=:account");
    query.bindValue(":account",account);
    query.exec();
    if (query.next()) {
        if (query.value(0).toString() == password) {
            return 1;
        } else {
            return 3;
        }
    }
    return 2;
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
