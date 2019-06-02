#pragma once

#include <string>

class Enemy {
public:
	Enemy() = default;
	virtual compl Enemy() = default;
	
	std::string name = "DefaultName";
	int hp = 50;
	int maxHp = hp;
	int atk = 20;
	int mag = 20;
	int exp = 25;
	int level = 1;
};

class Dummy : public Enemy {
public:
	Dummy();
	virtual compl Dummy() = default;
};

