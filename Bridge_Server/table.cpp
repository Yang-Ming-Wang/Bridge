#include "table.h"

Table::Table()
{
    currentPlayer = 0;
    turn = 0;
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
        seat[i].playerid = -1;
        seat[i].order = -1;
    }
}

void Table::addtable(int id)
{
    for (int i = 0;i < 4;i ++) {
        if (seat[i].playerid == -1) {
            mutex.lock();
            seat[i].playerid = id;
            seat[i].order = currentPlayer;
            currentPlayer++;
            if (currentPlayer == 4) {
                ready.wakeAll();
            }
            mutex.unlock();
            return ;
        }
    }
}

void Table::gettable(int clientID,int *arr)
{
    int index,j;

    mutex.lock();
    if (currentPlayer < 4) {
        ready.wait(&mutex);
    }

    mutex.unlock();
    if ((index = getIndexbyClientID(clientID)) != -1) {
        for (j = 0;j < 13;j++) {
            arr[j] = seat[index].card[j];
        }
    }
    return ;
}

int Table::leavetable(int id)
{
    for (int i = 0;i < 4;i ++) {
        if (seat[i].playerid == id) {
            mutex.lock();
            seat[i].playerid = -1;
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

void Table::setOrder(void)
{
    int i,index,color,diff,max,winner;
    for (index = 0; index < 4 && seat[index].order != 0;index++);
    if (index < 4) {
        color = seat[index].sendcard/13*13;
        max = 0;
        for (i = 0;i < 4;i++) {
            index = (index + 1) % 4;
            diff = seat[index].sendcard - color;
            if (diff < 13 && diff > max) {
                max = diff;
                winner = index;
            }
        }

        printf("winner [%d] use card [%d] to win!!\n",winner,seat[winner].sendcard);

        index = winner;
        turn = winner;
        for (i = 0;i < 4;i++) {
            seat[index].order = i;
            printf("client %d order %d\n",seat[index].playerid,seat[index].order);
            index = (index + 1) % 4;
        }
    }
}

int Table::getOrder(int clientID)
{
    int i;
    if ((i = getIndexbyClientID(clientID)) != -1) {
        return seat[i].order;
    }
    return i;
}

void Table::receive_card(int cardID)
{
    seat[turn].sendcard = cardID;
    printf("clientID %d recv Card = %d\n",seat[turn].playerid,seat[turn].sendcard);
    turn = (turn + 1) % 4;
}

int Table::getIndexbyClientID(int clientID)
{
    int i;
    for (i = 0;i < 4 && seat[i].playerid != clientID;i++);
    if (i < 4) {
        return i;
    }
    return -1;
}
