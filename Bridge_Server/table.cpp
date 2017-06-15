#include "table.h"

Table::Table()
{
    currentPlayer = 0;
    restart();
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
        seat[i].playerid = 0;
    }
}

void Table::addtable(int id)
{
    for (int i = 0;i < 4;i ++) {
        if (seat[i].playerid == 0) {
            mutex.lock();
            seat[i].playerid = id + 1;
            currentPlayer++;
            if (currentPlayer == 4)
                ready.wakeAll();
            mutex.unlock();
            return ;
        }
    }
}

void Table::gettable(int clientID,int *arr)
{
    int i,j;
    mutex.lock();
    if (currentPlayer != 4)
        ready.wait(&mutex);
    mutex.unlock();
    for (i = 0;i < 4;i++) {
        if (seat[i].playerid == clientID + 1) {
            for (j = 0;j < 13;j++) {
                arr[j] = seat[i].card[j];
            }
        }
    }
    return ;
}

int Table::leavetable(int id)
{
    for (int i = 0;i < 4;i ++) {
        if (seat[i].playerid == id) {
            mutex.lock();
            seat[i].playerid = 0;
            currentPlayer--;
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
        for (int j = 0;j < 13;j ++) {
            printf(" %d",seat[i].card[j]);
        }
        printf("\n");
    }
}
