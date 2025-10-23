#pragma once
#include "surface.h"
#include <string>

enum class ItemTypes {
	Animal,
	Plant,
	Fungi
};

struct Item {
	ItemTypes itemType;
	Tmpl8::Pixel color;
	float smell;
	float weight;
	std::string& name;
	Tmpl8::Sprite& sprite;
};