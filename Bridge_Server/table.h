#ifndef TABLE_H
#define TABLE_H

#include <QMutex>
#include <QTime>

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
    void shuffle(int *);
    int random[52];
    struct player{
        int cardnum,playerid,card[13];
    } seat[4];
};

#endif // TABLE_H
