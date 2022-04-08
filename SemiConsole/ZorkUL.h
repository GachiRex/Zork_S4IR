#ifndef ZORKUL_H_
#define ZORKUL_H_

#include <iostream>
#include <string>

#include <QFile>
#include <QStringList>
#include <QCoreApplication>
#include <QTextStream>

#include "Room.h"
#include "item.h"

#include "entity.h"

using namespace std;

class ZorkUL {
private:
    void createRooms();
    void createItems();
    void displayItems();
public:
    ZorkUL();
    Player *zorkPlayer;
    Room *currentRoom;
    map<string, Room*> roomList;
    void printWelcome();
	string go(string direction);
    QStringList ReadWordleData();
};

#endif /*ZORKUL_H_*/
