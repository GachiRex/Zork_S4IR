#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "entity.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;
    NPC NPCinRoom; //single NPC per room

public:
    int numberOfItems();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    bool isLocked;
    void addNPC(NPC inNPC, Room *room);
    NPC getNPC();
};

#endif
