#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"

#include "entity.h"

#include <iostream>
#include <string>
using namespace std;

class ZorkUL {
public:
//private:
    Player *zorkPlayer;
	Parser parser;
	Room *currentRoom;
    map<string, Room*> roomList;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
	void goRoom(Command command);
    void createItems();
    void displayItems();
    void createNpcs();
//public:
	ZorkUL();
	void play();
	string go(string direction);
//Custom functions
    void tele(Command command);
    vector<string> ReadWordleData(string path);
    void wordle();
};

#endif /*ZORKUL_H_*/
