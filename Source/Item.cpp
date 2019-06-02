#include "Item.h"
#include "Game.h"

void Item::Add(Item item) {
	if(item.num < 10) {
		item.num++;
    }
}

void Item::Remove(Item item) {
	if(item.num > 0) {
		item.num--;
    }
}

void Item::Show(void) {
	rlutil::cls();
	std::cout << "Name: " << name << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Value: " << value << std::endl;
}

Cure::Cure(string const& newName, string const& newDescription, int newValue, int newCurePoints) {
	name = newName;
	description = newDescription;
	value = newValue;
	CurePoints = newCurePoints;
}
