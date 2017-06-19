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
    int index;
    mutex.lock();
    if ((index = getIndexbyClientID(-1)) != -1) {
        seat[index].playerid = id;
        seat[index].order = currentPlayer;
        currentPlayer++;
        if (currentPlayer == 4) {
            ready.wakeAll();
        }
    } else {
        printf("can't add table\n");
    }
    mutex.unlock();
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

void Table::leavetable(int clientID)
{
    int index;
    if ((index = getIndexbyClientID(clientID)) != -1) {
        mutex.lock();
        seat[index].playerid = -1;
        currentPlayer--;
        if (currentPlayer > 0) {
            ready.wait(&mutex);
        } else {
            ready.wakeAll();
        }
        mutex.unlock();
        turn = 0;
        return ;
    }
    printf("table doesn't contain this id\n");
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

void Table::setOrder(int round)
{
    int i,color,diff,max,winner;

    //seat[i] must has one element order == 0
    for (i = 0;seat[i].order != 0;i++);

    color = seat[i].sendcard/13*13;
    max = 0;
    for (i = 0;i < 4;i++) {
        diff = seat[i].sendcard - color;
        if (diff < 13 && diff >= max) {
            max = diff;
            winner = i;
        }
    }

    printf("winner [%d] use card [%d] to win!!\n",winner,seat[winner].sendcard);

    turn = winner;
    result[round] = winner;
    for (i = 0;i < 4;i++) {
        seat[i].order = (i - winner + 4) % 4;
        printf("client %d order %d\n",seat[i].playerid,seat[i].order);
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

int Table::final_result(int clientID)
{
    int i,teamA,teamB;
    teamA = 0;
    teamB = 0;
    for (i = 0;i < 13;i++) {
       if (result[i] % 2 == 0) {
           teamA++;
       } else {
           teamB++;
       }
    }
    i = getIndexbyClientID(clientID);
    if (teamA > teamB && i % 2 == 0) {
        return 1;
    } else if (teamB > teamA && i % 2 != 0){
        return 1;
    }
    return 0;
}
