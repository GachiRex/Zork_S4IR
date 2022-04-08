#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <list>
#include <vector>
#include <QString>

#include "item.h"

class Entity {
protected:
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
    void setName(string inName);
    void setDescription(string inDesc);
    int getHP();
    int getMP();
};

class Player : public Entity {
private:
    float money;
    vector <Item> Inventory;
    int keyNb;
public:
    Player(string name, string description = "Descr", int hp = 20, int mp = 10) : money(0), keyNb(0)
    { this->name=name ; this->description = description; this->hp = hp; this->mp = mp; }
    Player(string name);
    ~Player() = default;
    void invAddItem(Item *item);
    void checkInventory();
    int getKeyNb();
    void buyItem(Item *item);
    void setMoney(int inMoney);
    void setKeyNb(int nb);
};

class NPC : public Entity {
private:
    vector <string> dialogList;
    int dialogNb;
public:
    NPC(string name, string description = "An NPC", int hp = 1, int mp = 1) : dialogNb(1)
    { this->name=name ; this->description = description; this->hp = hp; this->mp = mp; }
    NPC(string name);
    ~NPC() = default;
    void addDialog(string dialog);
    void coutDialog(int dialogNb);
    int getDialogNb();
    void setDialogNb(int inDialogNb);
    void operator -- () {
        --dialogNb;
    }
};

class Enemy : public Entity {
protected:
    int spwnRate;
    Item *drop;
    void setDrop(Item *inDrop);
public:
    Enemy(string name, string description, int hp, int mp, Item *dropint) : spwnRate(1)
    { this->setName(name); this->setDescription(description); this->setHP(hp); this->setMP(mp); this->setDrop(dropint);}
    Enemy(string name);
    Enemy(const Enemy &e1); //deep copy
    ~Enemy() = default;
    void setSpawnRate(float inSpwnRate);
    float getSpawnRate();
    Item* getDrop();
};

class Lionel : public NPC, public Enemy {
public:
    bool bigboss = true;
    Lionel(string name, string description);
    ~Lionel() = default;
};

#endif // ENTITY_H
