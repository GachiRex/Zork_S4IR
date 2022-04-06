#include <iostream>
#include <list>
#include <algorithm> //for find

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

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = new Room("a");
        //isLocked? default=0?
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
        a->addNPC(createNPC_Cindy(),a);
	b = new Room("b");
        b->addItem(new Item("xx", 3, 33));
        b->addItem(new Item("yy", 4, 44));
	c = new Room("c");
	d = new Room("d");
	e = new Room("e");
	f = new Room("f");
	g = new Room("g");
	h = new Room("h");
	i = new Room("i");

	j = new Room("j");
    k = new Room("k");
    l = new Room("l");
    m = new Room("m");

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

//Rooms with locked northern exits
    a->northLock(f);
    f->northLock(m);

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
	cout << "start"<< endl;
	cout << "info for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
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
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

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
