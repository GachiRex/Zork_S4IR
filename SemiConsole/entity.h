#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <list>
#include <vector>
#include "item.h"

class Entity {
private:
    string name;
    string description;
    int hp;
    int mp;
public:
    void CheckStats();
    void setName(string inName) { this->name = inName; }
    void setDescription(string inDesc){ this->description = inDesc; }
    void setHP(int inHP) { this->hp = inHP; }
    void setMP (int inMP) { this->mp = inMP; }
    string GetName() { return this->name; }
    string GetDescription() { return this->description; }
};

class Player : public Entity {
private:
    float money;
    vector <Item> Inventory;
public:
    void invAddItem(Item item);
    void checkInventory();
    void buyItem(Item item) { money -= item.getValue() ; invAddItem(item); }
    void setMoney(int inMoney) { this->money = inMoney; }
};

class NPC : public Entity {
private:
    vector <string> dialogList; //max nb of dialogs
public:
    void addDialog(string dialog);
    void coutDialog(int dialogNb) {
        cout << this->GetName() << ": " << dialogList[dialogNb] << endl;
    }
};

class Enemy : public Entity {
private:
    int spwnRate;
    list<Item> dropTable = list<Item>{3};
public:
    void SetSpawnRate (float inSpwnRate) { (inSpwnRate < 0 || inSpwnRate > 1) ? this->spwnRate = 0 : this->spwnRate = inSpwnRate; }
};

Player createPlayer(string name, string description = "Descr", int hp = 20, int mp = 10, int money = 0);
Enemy createMob(string name, string description, int hp, int mp, int spawnRate);
NPC createNPC(string name, string description = "[placeholder] An NPC", int hp = 1, int mp = 1);

#endif // ENTITY_H
