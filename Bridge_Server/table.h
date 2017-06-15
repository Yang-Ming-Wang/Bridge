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
private:
    QMutex mutex;
    QWaitCondition ready;
    void shuffle(int *);
    int random[52];
    int currentPlayer;
    struct player{
        int playerid,card[13];
    } seat[4];
};

#endif // TABLE_H
