#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"

void setupCreatureTypeList() {
	Sprite testSprite = Sprite("test", 1);
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal",
		0,
		testSprite,
		testSprite,
		testSprite,
		testSprite
	));
}