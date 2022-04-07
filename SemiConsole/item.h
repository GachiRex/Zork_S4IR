#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    string name;
	string description;
	string longDescription;
	int weightGrams;
	float value;
	bool weaponCheck;
    bool keyCheck;

public:
    Item (string inName, string inDescription, bool weaponCheck = 0, bool keyCheck = 0);
    string getName();
	string getShortDescription();
    string getLongDescription();
	int getWeight();
	void setWeight(int weightGrams);
	float getValue();
	void setValue(float value);
    bool getWeaponCheck();
    void setWeaponCheck(bool weaponCheck);
    bool getKeyCheck();
    void setKeyCheck(bool keyCheck);
};

#endif /*ITEM_H_*/
