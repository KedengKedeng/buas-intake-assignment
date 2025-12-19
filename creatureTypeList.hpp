#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"

void setupCreatureTypeList() {
	Sprite test = spriteRepository.get("test", 1.0f);
	AnimatedSprite testSprite = AnimatedSprite(std::vector<Sprite>{test}, 1.0f);
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal",
		0,
		testSprite,
		testSprite,
		testSprite,
		testSprite
	));
}