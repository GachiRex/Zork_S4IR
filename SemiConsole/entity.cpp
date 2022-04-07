#include "entity.h"

/** ENTITY FUNCTIONS **/

void Entity::CheckStats(){
    cout << endl
         << "Name: " << name << endl
         << "Desc: " << description << endl
         << "HP: " << hp << endl
         << "MP: " << mp << endl
         << endl;
}

void Entity::setName(string inName) {
    name = inName;
}
void Entity::setDescription(string inDesc){
    description = inDesc;
}
void Entity::setHP(int inHP) {
    hp = inHP;
}
void Entity::setMP (int inMP) {
    mp = inMP;
}
string Entity::GetName() {
    return name;
}
string Entity::GetDescription() {
    return description;
}

int Entity::getHP() {
    return hp;
}

int Entity::getMP() {
    return mp;
}

/** PLAYER FUNCTIONS **/

void Player::invAddItem(Item item) {
    if (Inventory.size() == 5) {
        cout << "[Inventory] Inventory is full!" << endl;
    }
    else {
        Inventory.push_back(item);
    }
}

void Player::checkInventory() {
    for ( unsigned long i = 0 ; i < Inventory.size() ; i++) {
            cout << endl
                 << "Item name: " << Inventory[i].getName() << endl
                 << "Item description: " << Inventory[i].getShortDescription() << endl
                 << "Item value: " << Inventory[i].getValue() << endl
                 << "Weapon? " << ((Inventory[i].getWeaponCheck()) ? "Yes" : "No") << endl
                 << "Key? " << ((Inventory[i].getKeyCheck()) ? "Yes" : "No") << endl
                 << endl;
    }
}

void Player::buyItem(Item item) {
    money -= item.getValue() ;
    invAddItem(item);
}

void Player::setMoney(int inMoney) {
    money = inMoney;
}

/** ENEMY FUNCTIONS **/

Enemy::Enemy(string name, string description, int hp, int mp, Item *drop, int spawnRate) {
    this->setName(name);
    this->setDescription(description);
    this->setHP(hp);
    this->setMP(mp);
    this->setSpawnRate(spawnRate);
    this->setDrop(drop);
}

void Enemy::setSpawnRate (float inSpwnRate) {
    (inSpwnRate < 0 || inSpwnRate > 1) ? spwnRate = 0 : spwnRate = inSpwnRate;
}

float Enemy::getSpawnRate() {
    return spwnRate;
}

void Enemy::setDrop(Item *inDrop) {
    drop = inDrop;
};

Item* Enemy::getDrop() {
    return drop;
};

/** NPC FUNCTIONS **/

NPC::NPC(string name, string description, int dialogNb, int hp, int mp) {
    this->setName(name);
    this->setDescription(description);

    this->setDialogNb(dialogNb);
    this->setHP(hp);
    this->setMP(mp);
}

void NPC::addDialog(string dialog) {
    if (dialogList.size() < 10) {
        dialogList.push_back(dialog);
    }
    else {
        cerr << "[debug] NPC already has 10 dialogs." << endl;
    }
}

void NPC::coutDialog(int dialogNb) {
    cout << endl
         << "["
         << this->GetName() << "]: "
         << dialogList[dialogNb]
         << endl;
}

int NPC::getDialogNb() {
    return dialogNb;
}
void NPC::setDialogNb(int inDialogNb) {
    dialogNb = inDialogNb;
}

/** CREATE FUNCTIONS --TEST**/

Player createPlayer(string name, string description, int hp, int mp, int money) {
    Player player;
    player.setName(name);
    player.setDescription(description);

    //default
    player.setHP(hp);
    player.setMP(mp);
    player.setMoney(money);

    /*//DELETE THIS ---------------Inventory test
    Item item;
    item.setName("Gros Caillou");
    item.setValue(0);
    item.setWeaponCheck(0);
    item.setKeyCheck(1);
    player.invAddItem(item);
    //*/

    return player;
}


