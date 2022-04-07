/*#include "CommandWords.h"

vector<string> CommandWords::validCommands;


CommandWords::CommandWords() {
	// Populate the vector if we haven't already.
	if (validCommands.empty()) {
		validCommands.push_back("go");
		validCommands.push_back("quit");
		validCommands.push_back("info");
		validCommands.push_back("map");
		validCommands.push_back("take");
		validCommands.push_back("put");
        //Custom functions
        validCommands.push_back("tele");
        validCommands.push_back("wordle");
    }
}

/
bool CommandWords::isCommand(string aString) {
	for (unsigned int i = 0; i < validCommands.size(); i++)
	{
		if (validCommands[i].compare(aString) == 0)
			return true;
	}
	// if we get here, the string was not found in the commands
	return false;
}

void CommandWords::showAll() {
	//Loops through validCommands and prints each to the screen.
	for (unsigned int i = 0; i < validCommands.size(); i++)
	{
		cout << validCommands[i]<< "  ";
	}
	cout << endl;
}
*/
