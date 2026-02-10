#include "creatureTypeRepository.hpp"
#include "spriteRepository.hpp"
#include "itemsRepository.hpp"

CreatureTypeRepository::CreatureTypeRepository() {
	constexpr float scale = 2;
	constexpr float frameRate = 0.005f;
	auto spriteRepo = spriteRepository();

	insert(std::make_shared<CreatureType>(
		CreatureTypes::BlueSlime,
		"Blue Slime",
		0,
		itemRepository().get(Items::BlueSlime),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::BlueSlimeWalkRight), frameRate, scale)
	));

	insert(std::make_shared<CreatureType>(
		CreatureTypes::GreenSlime,
		"Green Slime",
		10,
		itemRepository().get(Items::GreenSlime),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::GreenSlimeWalkRight), frameRate, scale)
	));

	insert(std::make_shared<CreatureType>(
		CreatureTypes::IceDragon,
		"Ice Dragon",
		20,
		itemRepository().get(Items::IceGem),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::IceDragonWalkRight), frameRate, scale)
	));

	insert(std::make_shared<CreatureType>(
		CreatureTypes::WindDragon,
		"Wind Dragon",
		30,
		itemRepository().get(Items::WindGem),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::WindDragonWalkRight), frameRate, scale)
	));

	insert(std::make_shared<CreatureType>(
		CreatureTypes::EarthDragon,
		"Earth Dragon",
		40,
		itemRepository().get(Items::EarthGem),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::EarthDragonWalkRight), frameRate, scale)
	));

	insert(std::make_shared<CreatureType>(
		CreatureTypes::FireDragon,
		"Fire Dragon",
		50,
		itemRepository().get(Items::FireGem),
		10.0f,
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonIdleLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonIdleRight), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonWalkLeft), frameRate, scale),
		AnimatedSprite(spriteRepo.getSheet(SpriteSheets::FireDragonWalkRight), frameRate, scale)
	));
}

void CreatureTypeRepository::insert(std::shared_ptr<CreatureType> creatureType) {
	registry_.insert({ creatureType->id, creatureType }); 
}

std::shared_ptr<CreatureType> CreatureTypeRepository::get(CreatureTypes type) { 
	return registry_.at(type); 
}

