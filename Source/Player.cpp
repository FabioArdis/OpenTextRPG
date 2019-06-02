#include "Player.h"

void Player::Use(Cure c) {
	hp += c.CurePoints;
	if(hp > maxHp) {
		hp = maxHp;
	}
	std::cout << name << " gained " << c.CurePoints << " HP.\n";
	std::cout << name << " HP = " << hp << std::endl;
}
