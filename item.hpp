#pragma once
#include "surface.h"
#include "animatedSprite.hpp"
#include <string>

enum class ItemTypes {
	Animal,
	Plant,
	Fungi,
	Product
};

struct Item {
	Item(ItemTypes itemType, const std::string& name, AnimatedSprite& sprite):
		itemType(itemType), name(name), sprite(sprite){};

	ItemTypes itemType;
	std::string name;
	AnimatedSprite sprite;
};