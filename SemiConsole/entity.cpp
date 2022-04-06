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

void Enemy::setSpawnRate (float inSpwnRate) {
    (inSpwnRate < 0 || inSpwnRate > 1) ? spwnRate = 0 : spwnRate = inSpwnRate;
}

float Enemy::getSpawnRate() {
    return spwnRate;
}

/** NPC FUNCTIONS **/

void NPC::addDialog(string dialog) {
    if (dialogList.size() < 10) {
        dialogList.push_back(dialog);
    }
    else {
        cout << "[debug] NPC already has 10 dialogs." << endl;
    }
}

void NPC::coutDialog(int dialogNb) {
    cout << endl
         << "[Dialog] "
         << this->GetName() << ": "
         << dialogList[dialogNb] << endl
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

    //DELETE THIS ---------------Inventory test
    Item item;
    item.setName("Gros Caillou");
    item.setValue(0);
    item.setWeaponCheck(0);
    item.setKeyCheck(1);
    player.invAddItem(item);
    //

    return player;
}

//create enemy test
Enemy createMob(string name, string description, int hp, int mp, int spawnRate) {
    Enemy mob;
    mob.setName(name);
    mob.setDescription(description);
    mob.setHP(hp);
    mob.setMP(mp);
    mob.setSpawnRate(spawnRate);
    return mob;
}

//create npc test
NPC createNPC(string name, string description, int dialogNb, int hp, int mp) {
    NPC npc;
    npc.setName(name);
    npc.setDescription(description);
    //default
    npc.setDialogNb(dialogNb);
    npc.setHP(hp);
    npc.setMP(mp);

    return npc;
}
