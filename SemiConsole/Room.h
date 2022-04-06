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
    bool isNorthLocked;
    bool isNPCpresent;

public:
    int numberOfItems();
    Room(string description, bool isNorthLocked = 0);
	void setExits(Room *north, Room *east, Room *south, Room *west);
    void northLock(Room *north); //lock north exit
    bool get_isNorthLocked();
    void set_isNorthLocked(bool flag);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    void addNPC(NPC inNPC, Room *room);
    void setNPCpresence(bool flag);
    bool getNPCpresence();
    NPC getNPC();
};

#endif
