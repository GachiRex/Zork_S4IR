#include "entity.h"

void Entity::CheckStats(){
    cout << endl
         << "Name: " << name << endl
         << "Desc: " << description << endl
         << "HP: " << hp << endl
         << "MP: " << mp << endl
         << endl;
}

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
                 << endl;
    }
}

//create player test
Player createPlayer(string name, string description, int hp, int mp, int money) {
    Player player;
    player.setName(name);
    player.setDescription(description);
    player.setHP(hp);
    player.setMP(mp);
    player.setMoney(money);

    //CHANGE THIS --test
    Item item;
    item.setName("Garbage");
    item.setValue(1);
    item.setWeaponCheck(0);
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
    mob.SetSpawnRate(spawnRate);
    return mob;
}
