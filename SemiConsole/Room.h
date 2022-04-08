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
    NPC* NPCinRoom;
    Enemy* MobInRoom;
    Lionel* LionelInRoom;
    bool isNorthLocked : 1;
    bool isNPCpresent : 1;
    bool isMobPresent : 1;
    bool isLionelPresent : 1;

public:
    /** Description **/
    int numberOfItems();
    Room(string description, bool isNorthLocked = 0);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    bool get_isNorthLocked();
    void set_isNorthLocked(bool flag);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    /** Items **/
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    Item* getItem(Room *room);
    void delItem(Room *room);
    /** Entities **/
    void addNPC(NPC *inNPC, Room *room);
    void setNPCpresence(bool flag);
    bool getNPCpresence();
    NPC* getNPC();
    void addMob(Enemy *inMob, Room *room, bool flag = 0); //If (flag) => Remove mob
    void setMobPresence(bool flag);
    bool getMobPresence();
    Enemy* getMob();
    void addLionel(Lionel *inLionel, Room *room);
    void setLIONELpresence(bool flag);
    bool getLIONELpresence();
    Lionel* getLionel();
    /** Room interaction **/
    void Bully(Player *player, Room *room);
    void Interact(Player *player, Room *room);
};

#endif
