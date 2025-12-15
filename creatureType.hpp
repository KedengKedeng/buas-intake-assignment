#pragma once
#include "sprite.hpp"
#include <string>

struct CreatureType {
	CreatureType(std::string& name, int price, Sprite& idleLeft, Sprite& idleRight, Sprite& walkLeft, Sprite& walkRight) :
		name(name), price(price), idleLeft(idleLeft), idleRight(idleRight), walkLeft(walkLeft), walkRight(walkRight) { }

	std::string name;
	int price;
	Sprite idleLeft;
	Sprite idleRight;
	Sprite walkLeft;
	Sprite walkRight;
};