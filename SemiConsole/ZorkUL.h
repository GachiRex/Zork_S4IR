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
    void createNpcs();
public:
    ZorkUL();
    Player *zorkPlayer;
    Room *currentRoom;
    map<string, Room*> roomList;
	void play();
    void printWelcome();
	string go(string direction);
    friend QStringList ReadWordleData();
    void wordle();
};

#endif /*ZORKUL_H_*/
