#ifndef TABLE_H
#define TABLE_H

#include <QMutex>
#include <QTime>

class Table
{
public:
    Table();
    void restart(void);
    int addtable(int);
    int leavetable(int);
    void showtable(void);
    struct player{
        int cardnum,playerid,card[13];
    } seat[4];
private:
    QMutex mutex;
    void shuffle(int *);
    int random[52];
};

#endif // TABLE_H
