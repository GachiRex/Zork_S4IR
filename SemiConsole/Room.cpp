#include "Room.h"
#include "Command.h"


Room::Room(string description, bool isNorthLocked) {
	this->description = description;
    this->isNorthLocked = isNorthLocked;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
	if (north != NULL)
		exits["north"] = north;
	if (east != NULL)
		exits["east"] = east;
	if (south != NULL)
		exits["south"] = south;
	if (west != NULL)
		exits["west"] = west;
}

bool Room::get_isNorthLocked() {
    return isNorthLocked;
}

void Room::set_isNorthLocked(bool flag){
    isNorthLocked = flag;
}

//Locks or unlocks northern exit of a room
void Room::northLock(Room *north) {
    bool flag = (get_isNorthLocked());
    exits["north"] = (flag == 0) ? north : NULL;
    set_isNorthLocked(flag);
}

string Room::shortDescription() {
	return description;
}

string Room::longDescription() {
    return "You are in room  " + description + ".\n" + displayItem() + exitString();
}

string Room::exitString() {
    string returnString = "\nYou realize you can go..";
	for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
        returnString += ", " + i->first;	// access the "first" element of the pair (direction as a string)
    if (get_isNorthLocked()) {
        returnString += "\nThe northern dooor seems locked";
    }
    if (getNPCpresence()) {
        returnString += "\nYou notice someone in the room:";
        returnString += "\nIt's " + getNPC()->GetName() + ". " + getNPC()->GetDescription() + "...";
    }
    if (getMobPresence()) {
        returnString += "\nYou notice someone dumb-looking in the room:";
        returnString += "\nIt's a " + getMob()->GetName() + ". " + getMob()->GetDescription() + "...";
    }
	return returnString;
}

Room* Room::nextRoom(string direction) {
	map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

string Room::displayItem() {
    string tempString = "You notice these things in the room: ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "There's nothing interesting in this room...";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getName() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

/** NPC functions  **/

void Room::addNPC(NPC *inNPC, Room *room) {
    room->NPCinRoom = inNPC;
    room->setNPCpresence(1);
}

NPC* Room::getNPC() {
    return NPCinRoom;
}

void Room::setNPCpresence(bool flag) {
    isNPCpresent = flag;
}

bool Room::getNPCpresence() {
    return isNPCpresent;
}

/** Mob functions  **/

void Room::addMob(Enemy *inMob, Room *room, bool flag) {
    if (flag) {
        room->MobInRoom = NULL;
        room->setMobPresence(0);
    }
    else {
        room->MobInRoom = inMob;
        room->setMobPresence(1);
    }
}

Enemy* Room::getMob() {
    return MobInRoom;
}

void Room::setMobPresence(bool flag) {
    isMobPresent = flag;
}

bool Room::getMobPresence() {
    return isMobPresent;
}

void Room::Bully(Player player, Room *room) {
    if (player.getMP() > room->getMob()->getMP()) {
        cout << "Your intimidated the " << room->getMob()->GetName() << " with your appearance. He dropped something while fleeing." << endl;
        room->addMob(room->getMob(), room, 1);
        //add inventory
    }
    else {
        if (player.getHP() > room->getMob()->getHP()) {
            cout << "You punch the " << room->getMob()->GetName() << " right in their face and search their pockets. You found something." << endl;
            room->addMob(room->getMob(), room, 1);
            //add inventory
        }
        else {
            cout << "You're not strong or intimidating enough to bully the " << room->getMob()->GetName() << ". Besides, it's not nice." << endl;
        }
    }
}
