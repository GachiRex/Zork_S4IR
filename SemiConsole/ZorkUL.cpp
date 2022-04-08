#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>

#include <QFile>
#include <QStringList>
#include <QCoreApplication>
#include <QTextStream>

using namespace std;

#include "ZorkUL.h"

ZorkUL::ZorkUL() {
    createRooms();
}

void ZorkUL::createRooms()  {
    /** Create the player **/
    Player *player;
    player = new Player("Player","The 'hero'");
    player->invAddItem(new Item("SPE Card","It's your SPE card. It's too worn out to be usable."));
    zorkPlayer = player;

    /** Creating the NPCs for the Rooms **/
    NPC *Maxime, *Cindy;
    Lionel *Brosius;
    string longDialog;

    Maxime = new NPC("Maxime Ouais-Sinon", "An obnoxious looking lady");
    Maxime->addDialog("Shoo! Shoo, sheeple!");
    longDialog += "Mine brother. Thee were did summon by Herr Prosious himself. Thee shalt findeth Prosious in the most northern room. ";
    longDialog += "However, thee shalt findeth two keys before meeting that gent. One to unlock this northern gate, another for the northern gate behind this northern gate. ";
    longDialog += "Now, begone and findeth the first key, maggot!\n";
    Maxime->addDialog(longDialog);
    longDialog.clear();

    Cindy = new NPC("Cindy l'Abrogée", "A strange little lady");
    Cindy->addDialog("... *she is staring at a blank screen*");
    longDialog += "You want to open the the Room A's north door? You should ask a SUP student to open it for you. ";
    longDialog += "I think there's one in J. OR was it in L? Wait, I'm just gonna look it up for you. Just wait.\n" ;
    Cindy->addDialog(longDialog);
    longDialog.clear();

    Brosius = new Lionel("Herr Lionel Prosious","A weird yet intimidating looking guy");
    longDialog += "Ach liebe Gott! This humiliation will not got unpunished! ";
    longDialog += "I shall isolate myself in this office and watch AKB48 now! Woe, woe upon you! ";
    longDialog += "Now be gone, wench!";
    Brosius->addDialog(longDialog);
    longDialog.clear();
    longDialog += "Ach, hello there. I summoned you about your MiMos. Can you explain to me why, at the end of June, you have only logged 30 minutes on Ionis? And 2 minutes on Projet Voltaire? ";
    longDialog += "Are you kidding me? LOL.";
    Brosius->addDialog(longDialog);

    /** Creating Enemies **/
    Enemy *ISG, *SUP, *ISG2;
    ISG = new Enemy("ISG student", "An hostile grocer", 21, 14, new Item("ISG Card","Useless. But pretty expensive."));
    SUP = new Enemy("SUP student", "A naive youngster", 19, 10, new Item("SUP Card","Could open A's door...", 0, 1));
    ISG2 = new Enemy(*ISG);

    /** Creating Rooms **/
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    //set second parameter to 1 if northLocked
    a = new Room("a",1);
        a->addNPC(Maxime,a);
    b = new Room("b");
        b->addNPC(Cindy,b);
    c = new Room("c");
        c->addItem(new Item("Nerdy shirt","A shirt with the ACDC logo on it. Intimidating enough...", 1));
	d = new Room("d");
	e = new Room("e");
    f = new Room("f",1);
    g = new Room("g");
        g->addMob(ISG2,g);
	h = new Room("h");
        h->addItem(new Item("Lionel's keycard","It isn't a key card. I think it's Nicolas' pokémon card. It reads 'Dracaufeu SV107'...",0,1));
	i = new Room("i");
	j = new Room("j");
        j->addMob(ISG,j);
    k = new Room("k");
    l = new Room("l");
        l->addMob(SUP,l);
    m = new Room("m");
        m->addLionel(Brosius,m);

    //Room list for tel
        roomList = {{"a", a},
                    {"b", b},
                    {"c", c},
                    {"d", d},
                    {"e", e},
                    {"f", f},
                    {"g", g},
                    {"h", h},
                    {"i", i},
                    {"j", j},
                    {"k", k},
                    {"l", l},
                    {"m", m}};


//             (N, E, S, W)
        a->setExits(f, b, d, c);
        b->setExits(NULL, NULL, NULL, a);
        c->setExits(NULL, a, NULL, NULL);
        d->setExits(a, e, NULL, i);
        e->setExits(NULL, NULL, l, d);
        f->setExits(m, g, a, h);
        g->setExits(NULL, NULL, NULL, f);
        h->setExits(NULL, f, NULL, NULL);
        i->setExits(NULL, d, j, NULL);

        j->setExits(i, k, NULL, NULL);
        k->setExits(NULL, l, NULL, j);
        l->setExits(e, NULL, NULL, k);
        m->setExits(NULL, NULL, f, NULL);


        currentRoom = a;
}

void ZorkUL::printWelcome() {
    cout << "You awake in a mysterious yet familiar looking room"<< endl;
    cout << "A lady is sitting in a chair. She seems busy with her computer"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}

QStringList ZorkUL::ReadWordleData(){
    QFile ifile("dictionary.txt");
    try{
        if (!ifile.exists()) { throw 2; }
    } catch(int x) {
        qDebug() << "Error" << x << ": Path doesn't lead anywhere. Aborting Wordle...";
        qDebug() << "Error happened in app path : " << qApp->applicationDirPath();
        exit(0);
    }

    ifile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString content = ifile.readAll();
    QStringList list = content.split(" ");
    return list;
}
