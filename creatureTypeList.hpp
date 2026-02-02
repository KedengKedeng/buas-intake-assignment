#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"
#include "itemsRepository.hpp"

void setupCreatureTypeList() {
	const float playerInteractionOffset = 10.0f;
	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto playerIdleLeft = AnimatedSprite(spriteRepository.getSheet("playeridleleft"), playerSpriteFrameRate, playerSpriteScale);
	auto playerIdleRight = AnimatedSprite(spriteRepository.getSheet("playeridleright"), playerSpriteFrameRate, playerSpriteScale);
	auto playerWalkLeft = AnimatedSprite(spriteRepository.getSheet("playerwalkleft"), playerSpriteFrameRate, playerSpriteScale);
	auto playerWalkRight = AnimatedSprite(spriteRepository.getSheet("playerwalkright"), playerSpriteFrameRate, playerSpriteScale);

	auto item = itemRepository.get("testItem2");
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal",
		0,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal2",
		100,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal3",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal4",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal5",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal6",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal7",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal8",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));
}