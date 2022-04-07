#include <iostream>
#include <list>
#include <algorithm> //for find
#include <fstream>

using namespace std;
#include "ZorkUL.h"
#include "characters.h"

/*int main (int argc, char* argv[]) {
	ZorkUL temp;
	temp.play();
	return 0;
}*/

ZorkUL::ZorkUL() {
    createRooms();
}

/*void ZorkUL::createNpcs() {
    NPC *Maxime, *Cindy;
    string longIntro;

    Maxime = new NPC("Maxime Ouais-Sinon", "An obnoxious looking lady");
    longIntro = "";
    longIntro += "Mine brother. Thee were did summon by Herr Prosious himself. Thee shalt findeth Prosious in the most northern room. ";
    longIntro += "However, thee shalt findeth two keys before meeting that gent. One to unlock this northern gate, another for the northern gate behind this northern gate. ";
    longIntro += "Now, begone and findeth the first key, maggot!\n";
    Maxime->addDialog("Shoo! Shoo, sheeple!");
    Maxime->addDialog(longIntro);

    Cindy = new NPC("Cindy l'Abrogée", "A strange little lady");
    Cindy->addDialog("Ayaaa ISSOU!");
    Cindy->addDialog("Lionel ce fou...");
}*/

void ZorkUL::createRooms()  {
    /** Create the player **/
    Player *player;
    player = new Player("Player","The 'hero'");
    player->invAddItem(new Item("SPE Card","It's your SPE card. It's too worn out to be usable."));
    zorkPlayer = player;

    /** Creating the NPCs for the Rooms **/
    NPC *Maxime, *Cindy, *Lionel;
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

    Lionel = new NPC("Herr Lionel Prosious","A weird yet intimidating looking guy");
    longDialog += "Ach liebe Gott! How did you beat me?! This humiliation will not got unpunished! ";
    longDialog += "I shall isolate myself in this office and watch AKB48 now! Woe, woe upon you!";
    Lionel->addDialog(longDialog);
    longDialog.clear();
    longDialog += "Ach, hello there. I summoned you about your MiMos. Can you explain to me why, at the end of June, you have only logged 30 minutes on Ionis? And 2 minutes on Projet Voltaire? ";
    longDialog += "Are you kidding me? LOL. I can cancel your prépa at any time. But as an infinitely good and merciful being, I'm willing to pass you on if you solve my Mordle. ";
    longDialog += "It's a worlde-like thing I coded during your OCR.";
    Lionel->addDialog(longDialog);

    /** Creating Enemies **/
    Enemy *ISG, *SUP;
    ISG = new Enemy("ISG student", "An hostile grocer", 21, 14, new Item("ISG Card","Useless. But pretty expensive."));
    SUP = new Enemy("SUP student", "A naive youngster", 19, 10, new Item("SUP Card","Could open A's door...", 0, 1));

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
	h = new Room("h");
        h->addItem(new Item("Lionel's keycard","It isn't a key card. I think it's Nicolas' pokémon card. It reads 'Dracaufeu SV107'...",0,1));
	i = new Room("i");
	j = new Room("j");
        j->addMob(ISG,j);
        //delete(ISG); ?
    k = new Room("k");
    l = new Room("l");
        l->addMob(SUP,l);
        //delete(SUP); ?
    m = new Room("m");
        m->addNPC(Lionel,m);

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

/**
 *  Main play routine.  Loops until end of play.
 */
/*void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}*/

void ZorkUL::printWelcome() {
    cout << "You awake in a mysterious yet familiar looking room"<< endl;
    cout << "A lady is sitting in a chair. She seems busy with her computer"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}
void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();

}
void ZorkUL::wordle() {
    string wordList[15] = {"pearl", "sewed", "moist", "croze","crane",
                          "bread", "short", "blunt", "flock", "greek",
                          "candy", "worry", "towel", "short", "stock"
                         };

    string display = "_____";
    string remLetters = " a b c d e f g h i j k l m n o p q r s t u v w x y z";
    string ranWord = wordList[rand() % 15];
    int solved = 0, remAttempts = 6;
    string guess;

    //cout << "[debug] ranWord is: "<< ranWord << endl;
    cout << "Your guess must contain ONLY lowercase letters" << endl;

    while (remAttempts > 0 && solved < 5) {
        cout << endl << "Remaining attempts: " <<  remAttempts << endl << remLetters << endl << display << endl << "Your guess: ";
        cin >> guess;
        string incorrectLetters = "";

        if (guess.length() < 6) {
            solved = 0;
            int i = 0;
            while (i < 5 && solved < 5) {
                string correctLetter = "";

                if (ranWord.find(guess[i]) != string::npos) {             //'string::npos' represents a non-position
                    correctLetter += guess[i];

                    if (guess[i] == ranWord[i]) {
                        remLetters.at((guess[i] - 96) * 2 - 1) = '_';    //'-96' because 'a'=97, '*2' because letters are separated by a space

                        unsigned long j = 0;
                        while (j < guess.length()) {
                            if (guess[i]==ranWord[j]) {
                                display[j] = guess[i];
                            }
                            j++;
                        }
                        solved++;
                    }
                    else {
                        cout << "The letter " << correctLetter << " is correct, but in the wrong spot" << endl;
                    }
                }
                else {
                    if ( (guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z')) {
                        incorrectLetters += ' ';
                        incorrectLetters += guess[i];
                        incorrectLetters += ' ';
                        remLetters.at((guess[i] - 96) * 2 - 1) = '_';
                    }
                }

                i++;
            }
            if (incorrectLetters != "") {
                cout << "Incorrect letters:" << incorrectLetters << " " << endl;
            }
            remAttempts--;
        }
        else {
            cout << "Your guess must be a word of 5 letters" << endl;
        }
    }

    if (solved == 5) {
        cout << endl << "You found the correct word!" << endl<<endl;
    }
    else {
        cout << endl << "You ran out of attempts!" << endl << "The word was: " << ranWord << endl<<endl;
    }
}

vector<string> ZorkUL::ReadWordleData(string path){
    ifstream src(path);
    vector<string> Dico;

    if (!src)
    {
      cerr << "[ZorkUL::ReadWordleData] Incorrect path. The worlde game will not function." << endl;
      exit(1);
    }
    string word;
    while(src >> word)
    {
      // TO DO remove unwanted characters from word
      cout << word << endl;  //Just for testing
      Dico.push_back(word);
    }

    system("pause");
    return Dico;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */

/*
 *
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
    if (commandWord.compare("tele") == 0)
        tele(command);
    else if (commandWord.compare("wordle") == 0)
        wordle();

    else if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        cout << "        [l]        " << endl;
        cout <<           |         " << endl;
        cout << "[h] --- [f] --- [g]" << endl;
		cout << "         |         " << endl;
        cout << "         |         " << endl;
		cout << "[c] --- [a] --- [b]" << endl;
		cout << "         |         " << endl;
		cout << "         |         " << endl;
		cout << "[i] --- [d] --- [e]" << endl;

		//New room j: map location
		cout << " |               |" << endl;
		cout << " |               |" << endl;
		cout << "[j] --- [k] --- [m]" << endl;

		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
        cout << "index number " << + location << endl;
        cout << endl;
        cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }

    {
    if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }

    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
            return true;
	}
	return false;
}*/

/** COMMANDS **/


/*void ZorkUL::goRoom(Command command) {
	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
		cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
}*/

/*string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}*/

/*void ZorkUL::tele(Command command) {
    if (!command.hasSecondWord()) {
        string strRoomList[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
        string ranDst = strRoomList[rand()%10];

        cout << "[Teleportation] teleported to a random room: room  "<< ranDst << endl;
        currentRoom = roomList[ranDst];
        cout << currentRoom->longDescription() << endl;
        return;
    }

    string dst = command.getSecondWord();
    if (!roomList[dst]) {
        cout << "there's no such room"<< endl;
        return;
    }

    cout << "teleported to room " << dst << endl;
    currentRoom = roomList[dst];
    cout << currentRoom->longDescription() << endl;
    return;
}*/

//Worlde like game test function

