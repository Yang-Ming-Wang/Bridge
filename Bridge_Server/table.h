#ifndef TABLE_H
#define TABLE_H

#include <QMutex>
#include <QTime>
#include <QWaitCondition>

class Table
{
public:
    Table();
    void restart(void);
    void addtable(int);
    int leavetable(int);
    void showtable(void);
    void gettable(int,int*);
    void setOrder(int);
    int getOrder(int);
    void receive_card(int);
    int final_result(int);
private:
    int getIndexbyClientID(int);
    QMutex mutex;
    QWaitCondition ready;
    void shuffle(int *);
    int random[52];
    int result[13];
    int currentPlayer;
    int turn;
    struct player{
        int playerid,order,sendcard,card[13];
    } seat[4];
};

#endif // TABLE_H
