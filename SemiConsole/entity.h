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
    void setHP(int inHP);
    void setMP (int inMP);
    string GetName();
    string GetDescription();
    int getHP();
    int getMP();
protected:
    void setName(string inName);
    void setDescription(string inDesc);
};

class Player : public Entity {
private:
    float money;
    vector <Item> Inventory;
    int keyNb;
public:
    Player(string name, string description = "Descr", int hp = 20, int mp = 10, int money = 0, int keyNb = 0);
    Player(string name);
    void invAddItem(Item *item);
    void checkInventory();
    void buyItem(Item *item);
    void setMoney(int inMoney);
    int getKeyNb();
    void setKeyNb(int nb);
};

class NPC : public Entity {
private:
    vector <string> dialogList;
    int dialogNb;
    bool isLionel;
public:
    NPC(string name, string description = "An NPC", int dialogNb = 1, int hp = 1, int mp = 1, bool LionelFlag = 0);
    NPC(string name);
    void addDialog(string dialog);
    void coutDialog(int dialogNb);
    int getDialogNb();
    void setDialogNb(int inDialogNb);
    bool getLionel();
};

class Enemy : public Entity {
private:
    int spwnRate;
    Item *drop;
public:
    Enemy(string name, string description, int hp, int mp, Item *dropint, int spawnRate = 1);
    Enemy(string name);
    void setSpawnRate(float inSpwnRate);
    float getSpawnRate();
    void setDrop(Item *inDrop);
    Item* getDrop();
};

#endif // ENTITY_H
