#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"

void setupCreatureTypeList() {
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		std::string("testAnimal"),
		0,
		Sprite(std::string("test"), 1),
		Sprite(std::string("test"), 1),
		Sprite(std::string("test"), 1),
		Sprite(std::string("test"), 1)
	));
}