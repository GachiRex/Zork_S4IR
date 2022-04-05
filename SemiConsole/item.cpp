#include "item.h"

Item::Item() {}

Item::Item (string inDescription, int inWeightGrams, float inValue) {
	description = inDescription;
	setWeight(inWeightGrams);
    value = inValue;
}

Item::Item(string inDescription) {
	description = inDescription;
}

string Item::getName() {
    return name;
}

void Item::setName(string inName) {
    name = inName;
}

void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
	   value = inValue;
}

void Item::setWeaponCheck(bool inWeaponCheck) {
    weaponCheck = inWeaponCheck;
}

string Item::getShortDescription()
{
	return description;
}

string Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}

float Item::getValue() {
    return value;
}

bool Item::getWeaponCheck() {
    return weaponCheck;
}


