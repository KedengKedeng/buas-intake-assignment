#pragma once
#include "surface.h"
#include "sprite.hpp"
#include <string>

enum class ItemTypes {
	Animal,
	Plant,
	Fungi
};

struct Item {
	Item(ItemTypes itemType, Tmpl8::Pixel color, float smell, float weight, const std::string& name, Sprite& sprite):
		itemType(itemType), color(color), smell(smell), weight(weight), name(name), sprite(sprite){};

	ItemTypes itemType;
	Tmpl8::Pixel color;
	float smell;
	float weight;
	std::string name;
	Sprite sprite;
};