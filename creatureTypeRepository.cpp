#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"
#include "itemsRepository.hpp"

CreatureTypeRepository::CreatureTypeRepository() {
	const float playerInteractionOffset = 10.0f;
	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto spriteRepo = spriteRepository();
	auto playerIdleLeft = AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeIdleLeft), playerSpriteFrameRate, playerSpriteScale);
	auto playerIdleRight = AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeIdleRight), playerSpriteFrameRate, playerSpriteScale);
	auto playerWalkLeft = AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeWalkLeft), playerSpriteFrameRate, playerSpriteScale);
	auto playerWalkRight = AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeWalkRight), playerSpriteFrameRate, playerSpriteScale);

	auto item = itemRepository.get("testItem2");
	insert(CreatureTypes::BlueSlime, std::make_shared<CreatureType>(
		"Blue Slime",
		0,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	insert(CreatureTypes::GreenSlime, std::make_shared<CreatureType>(
		"Green Slime",
		0,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	insert(CreatureTypes::IceDragon, std::make_shared<CreatureType>(
		"Ice Dragon",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	insert(CreatureTypes::WindDragon, std::make_shared<CreatureType>(
		"Wind Dragon",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	insert(CreatureTypes::EarthDragon, std::make_shared<CreatureType>(
		"Earth Dragon",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));

	insert(CreatureTypes::FireDragon, std::make_shared<CreatureType>(
		"Fire Dragon",
		20,
		item,
		10.0f,
		playerIdleLeft,
		playerIdleRight,
		playerWalkLeft,
		playerWalkRight
	));
}

void CreatureTypeRepository::insert(CreatureTypes identifier, std::shared_ptr<CreatureType> creatureType) {
	registry_.insert({ identifier, creatureType }); 
}

std::shared_ptr<CreatureType> CreatureTypeRepository::get(CreatureTypes type) { 
	return registry_.at(type); 
}

