#include "table.h"

Table::Table()
{
    shuffle(random);
    for (int i = 0;i < 13;i ++) {
        seat[0].card[i] = random[4 * i + 0];
        seat[1].card[i] = random[4 * i + 1];
        seat[2].card[i] = random[4 * i + 2];
        seat[3].card[i] = random[4 * i + 3];
    }
    for (int i = 0;i < 4;i ++) {
        seat[i].cardnum = 13;
    }
}

void Table::shuffle(int *arr)
{
    int i,temp,index;
    qsrand(QTime::currentTime().msec());
    for (i = 0; i < 52; i++) {
        arr[i] = i;
    }
    for (i = 52; i > 0; i--) {
        index = qrand() % i;
        temp = arr[index];
        arr[index] = arr[i - 1];
        arr[i - 1] = temp;
    }
}

void Table::restart(void)
{
    shuffle(random);
    for (int i = 0;i < 13;i ++) {
        seat[0].card[i] = random[4 * i + 0];
        seat[1].card[i] = random[4 * i + 1];
        seat[2].card[i] = random[4 * i + 2];
        seat[3].card[i] = random[4 * i + 3];
    }
    for (int i = 0;i < 4;i ++) {
        seat[i].cardnum = 13;
        seat[i].playerid = 0;
    }
}

int Table::addtable(int id)
{
    for (int i = 0;i < 4;i ++) {
        if (seat[i].playerid == 0) {
            mutex.lock();
            seat[i].playerid = id;
            mutex.unlock();
            return i +1;
            }
    }
    return 0;
}

int Table::leavetable(int id)
{
    for (int i = 0;i < 4;i ++) {
        if (seat[i].playerid == id) {
            mutex.lock();
            seat[i].playerid = 0;
            mutex.unlock();
            return i + 1;
        }
    }
    return 0;
}

void Table::showtable(void)
{
    for (int i = 0;i < 4;i ++) {
        printf("player %d has",seat[i].playerid);
        for (int j =0;j < seat[i].cardnum;j ++) {
            printf(" %d",seat[i].card[j]);
        }
        printf("\n");
    }
}
