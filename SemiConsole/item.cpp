#include "item.h"

Item::Item (string inName, string inDescription, bool armorCheck, bool keyCheck) {
    this->name = inName;
    this->description = inDescription;
    this->armorCheck = armorCheck;
    this->keyCheck = keyCheck;
}

//setters&getters

string Item::getName() {
    return name;
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

float Item::getValue() {
    return value;
}

void Item::setKeyCheck(bool inKeyCheck) {
    keyCheck = inKeyCheck;
}

bool Item::getKeyCheck() {
    return keyCheck;
}

void Item::setArmorCheck(bool inArmorCheck) {
    armorCheck = inArmorCheck;
}

bool Item::getArmorCheck() {
    return armorCheck;
}

string Item::getShortDescription()
{
	return description;
}

string Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}