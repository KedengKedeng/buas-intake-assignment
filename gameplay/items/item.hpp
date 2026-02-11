#pragma once
#include "animatedSprite.hpp"
#include "items.hpp"
#include <string>

struct Item {
	Item(Items id, const std::string& name, int value, AnimatedSprite& sprite):
		id(id), name(name), value(value), sprite(sprite){};

	std::string name;
	AnimatedSprite sprite;
	int value;
	Items id;
};