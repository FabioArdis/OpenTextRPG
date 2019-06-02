#pragma once

#include <string>
#include "Item.h"

using namespace std;

class Player final {
public:
	Player() = default;
	virtual compl Player() = default;
	
	string name = "PlayerName";
	string surname = "PlayerSurname";
	string playerclass = "Test";
	int hp = 50;
	int atk = 20;
	int mag = 20;
	int exp = 0;
	int maxHp = 50;
	int level = 1;
	int nextlevel = 15;
	int actualZone = 1;
	int x = 3;
	int y = 3;
	
	void Use(Cure c);
};
