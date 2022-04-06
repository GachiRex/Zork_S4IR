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
    void setName(string inName);
    void setDescription(string inDesc);
    void setHP(int inHP);
    void setMP (int inMP);
    string GetName();
    string GetDescription();
};

class Player : public Entity {
private:
    float money;
    vector <Item> Inventory;
public:
    void invAddItem(Item item);
    void checkInventory();
    void buyItem(Item item);
    void setMoney(int inMoney);
};

class NPC : public Entity {
private:
    vector <string> dialogList;
    int dialogNb;
public:
    void addDialog(string dialog);
    void coutDialog(int dialogNb);
    int getDialogNb();
    void setDialogNb(int inDialogNb);
};

class Enemy : public Entity {
private:
    int spwnRate;
    list<Item> dropTable = list<Item>{3};
public:
    void setSpawnRate(float inSpwnRate);
    float getSpawnRate();
};

Player createPlayer(string name, string description = "Descr", int hp = 20, int mp = 10, int money = 0);
Enemy createMob(string name, string description, int hp, int mp, int spawnRate);
NPC createNPC(string name, string description = "An NPC", int dialogNb = 2, int hp = 1, int mp = 1);

#endif // ENTITY_H
