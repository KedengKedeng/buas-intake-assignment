#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"
#include "itemsRepository.hpp"

CreatureTypeRepository::CreatureTypeRepository() {
	const float playerInteractionOffset = 10.0f;
	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto spriteRepo = spriteRepository();

	insert(CreatureTypes::BlueSlime, std::make_shared<CreatureType>(
		"Blue Slime",
		0,
		itemRepository.get("Blue Slime"),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeWalkRight), playerSpriteFrameRate, playerSpriteScale)
	));

	insert(CreatureTypes::GreenSlime, std::make_shared<CreatureType>(
		"Green Slime",
		0,
		itemRepository.get("Green Slime"),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeWalkRight), playerSpriteFrameRate, playerSpriteScale)
	));

	insert(CreatureTypes::IceDragon, std::make_shared<CreatureType>(
		"Ice Dragon",
		0,
		itemRepository.get("Ice Gem"),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonWalkRight), playerSpriteFrameRate, playerSpriteScale)
	));

	insert(CreatureTypes::WindDragon, std::make_shared<CreatureType>(
		"Wind Dragon",
		0,
		itemRepository.get("Wind Gem"),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonWalkRight), playerSpriteFrameRate, playerSpriteScale)
	));

	insert(CreatureTypes::EarthDragon, std::make_shared<CreatureType>(
		"Earth Dragon",
		0,
		itemRepository.get("Earth Gem"),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonWalkRight), playerSpriteFrameRate, playerSpriteScale)
	));

	insert(CreatureTypes::FireDragon, std::make_shared<CreatureType>(
		"Fire Dragon",
		0,
		itemRepository.get("Fire Gem"),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonWalkRight), playerSpriteFrameRate, playerSpriteScale)
	));
}

void CreatureTypeRepository::insert(CreatureTypes identifier, std::shared_ptr<CreatureType> creatureType) {
	registry_.insert({ identifier, creatureType }); 
}

std::shared_ptr<CreatureType> CreatureTypeRepository::get(CreatureTypes type) { 
	return registry_.at(type); 
}

