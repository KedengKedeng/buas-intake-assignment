#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"

void setupCreatureTypeList() {
	Sprite testSprite = Sprite(std::string("test"), 1);
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		std::string("testAnimal"),
		0,
		testSprite,
		testSprite,
		testSprite,
		testSprite
	));
}