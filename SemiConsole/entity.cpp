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

Player::Player(string name, string description, int hp, int mp, int money, int keyNb) {
    this->setName(name);
    this->setDescription(description);

    this->setHP(hp);
    this->setMP(mp);
    this->setMoney(money);

    this->setKeyNb(keyNb);
};

void Player::invAddItem(Item *item) {
    Inventory.push_back(*item);
    if ( item->getKeyCheck() ) {
        setKeyNb(getKeyNb() + 1);
    }
}

void Player::checkInventory() {
    cout << endl
         << "In your tiny pocket, you have:"
         << endl;
    for ( unsigned long i = 0 ; i < Inventory.size() ; i++) {
            cout << endl << i + 1 << ". "
                 << "Item name: " << Inventory[i].getName() << endl
                 << "Item description: " << Inventory[i].getShortDescription() << endl
                 << "Armor? " << ((Inventory[i].getArmorCheck()) ? "Yes, +5 Intimidation" : "No") << endl
                 << "Key? " << ((Inventory[i].getKeyCheck()) ? "Yes" : "No") << endl
                 << endl;
    }
}

void Player::buyItem(Item *item) {
    money -= item->getValue() ;
    invAddItem(item);
}

void Player::setMoney(int inMoney) {
    money = inMoney;
}

int Player::getKeyNb() {
    return keyNb;
}

void Player::setKeyNb(int nb) {
    keyNb = nb;
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

Enemy::Enemy(string name) {
    this->setName(name);
    this->setDescription("[PH]");
    this->setHP(1);
    this->setMP(1);
    this->setSpawnRate(1);
    this->setDrop(new Item("PH","PH"));
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

NPC::NPC(string name, string description, int dialogNb, int hp, int mp, bool lionelCheck) {
    this->setName(name);
    this->setDescription(description);

    this->setDialogNb(dialogNb);
    this->setHP(hp);
    this->setMP(mp);
    this->isLionel = lionelCheck;
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

bool NPC::getLionel() {
    return isLionel;
}

