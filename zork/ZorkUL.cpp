#include <iostream>

using namespace std;
#include "ZorkUL.h"

int main (int argc, char* argv[]) {
	ZorkUL temp;
	temp.play();
	return 0;
}

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {
	Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

	a = new Room("a");
        a->addItem(new Item("x", 1, 11));
        a->addItem(new Item("y", 2, 22));
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

	//New room: j
	j = new Room("j");

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
                {"j", j}};


//             (N, E, S, W)
	a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
	d->setExits(a, e, NULL, i);
	e->setExits(NULL, NULL, NULL, d);
	f->setExits(NULL, g, a, h);
	g->setExits(NULL, NULL, NULL, f);
	h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, j, NULL);

    //New room : j
    j->setExits(i, NULL, NULL, NULL);

        currentRoom = a;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
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
}

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
        cout << "[h] --- [f] --- [g]" << endl;
		cout << "         |         " << endl;
        cout << "         |         " << endl;
		cout << "[c] --- [a] --- [b]" << endl;
		cout << "         |         " << endl;
		cout << "         |         " << endl;
		cout << "[i] --- [d] --- [e]" << endl;

		//New room j: map location
		cout << " |                 " << endl;
		cout << " |                 " << endl;
		cout << "[j]                " << endl;

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
    /*
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
*/
    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
			cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::goRoom(Command command) {
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
}

string ZorkUL::go(string direction) {
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
}

//Teleportatio function

void ZorkUL::tele(Command command) {
    if (!command.hasSecondWord()) {
        string strRoomList[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
        string ranDst = strRoomList[rand()%10];

        cout << "teleported to a random room: room  "<< ranDst << endl;
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
}

//Worlde like game test function

void ZorkUL::wordle() {
    string wordList[15] = {"pearl", "sewed", "moist", "croze","crane",
                          "bread", "short", "blunt", "flock", "greek",
                          "candy", "worry", "towel", "short", "stock"
                         };
    string display = "_____";
    string ranWord = wordList[rand() % 15];
    int solved = 0, remAttempts = 6;
    string guess;

    //cout << "[debug] ranWord is: "<< ranWord << endl;
    while (remAttempts > 0 && solved < 5) {
        cout << display << endl << "Remaining attempts: " <<  remAttempts << endl << "Your guess is: ";
        cin >> guess;

        if (guess.length() < 6) {
            solved = 0;
            int i = 0;
            while (i < 5 && solved < 5) {
                string correctLetters = "";

                if (ranWord.find(guess[i]) != string::npos) {       //'string::npos' represents a non-position
                    correctLetters += guess[i];

                    if (guess[i] == ranWord[i]) {
                        display[i] = guess[i];
                        solved++;
                    }
                    else {
                        cout << "The letter " << correctLetters << " is correct, but in the wrong spot" << endl;
                    }
                }

                i++;
            }
            remAttempts--;
        }
        else {
            cout << "Your guess must be a word of 5 letters" << endl;
        }
    }

    if (solved == 5) {
        cout << "You found the correct word!" << endl;
    }
    else {
        cout << "You ran out of attempts!" << endl << "The word was: " << ranWord << endl;
    }
}
