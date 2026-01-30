#pragma once
#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"

void setupCreatureTypeList() {
	const float playerInteractionOffset = 10.0f;
	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto playerIdleLeft = AnimatedSprite(spriteRepository.getSheet("playeridleleft"), playerSpriteFrameRate, playerSpriteScale);
	auto playerIdleRight = AnimatedSprite(spriteRepository.getSheet("playeridleright"), playerSpriteFrameRate, playerSpriteScale);
	auto playerWalkLeft = AnimatedSprite(spriteRepository.getSheet("playerwalkleft"), playerSpriteFrameRate, playerSpriteScale);
	auto playerWalkRight = AnimatedSprite(spriteRepository.getSheet("playerwalkright"), playerSpriteFrameRate, playerSpriteScale);
	creatureTypeRepository.insert(std::make_shared<CreatureType>(
		"testAnimal",
		0,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));
}