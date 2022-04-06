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
                 << "Key? " << ((Inventory[i].getKeyCheck()) ? "Yes" : "No") << endl
                 << endl;
    }
}

void NPC::addDialog(string dialog) {
    if (dialogList.size() < 10) {
        dialogList.push_back(dialog);
    }
    else {
        cout << "[debug] NPC already has 10 dialogs." << endl;
    }
}

//create player test
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
    mob.SetSpawnRate(spawnRate);
    return mob;
}

//create npc test
NPC createNPC(string name, string description, int hp, int mp) {
    NPC npc;
    npc.setName(name);
    npc.setDescription(description);

    //default
    npc.setHP(hp);
    npc.setMP(mp);

    return npc;
}
