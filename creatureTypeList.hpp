#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"

void setupCreatureTypeList() {
	AnimatedSprite testSprite = AnimatedSprite(spriteRepository.get("test", 1.0f), 1.0f);
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal",
		0,
		testSprite,
		testSprite,
		testSprite,
		testSprite
	));
}