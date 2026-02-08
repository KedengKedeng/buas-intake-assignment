#pragma once
#include "animatedSprite.hpp"
#include "items.hpp"
#include <string>

struct Item {
	Item(Items id, const std::string& name, AnimatedSprite& sprite):
		id(id), name(name), sprite(sprite){};

	Items id;
	std::string name;
	AnimatedSprite sprite;
};