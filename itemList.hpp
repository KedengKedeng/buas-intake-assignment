#pragma once
#include "itemsRepository.hpp"
#include "spriteRepository.hpp"
#include "recipeBook.hpp"

void setupItemList() {
	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"Blue Slime",
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository().get(Sprites::BlueSlime, 1.0f) }), 0.0f, 1.0f)
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"Green Slime",
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository().get(Sprites::GreenSlime, 1.0f) }), 0.0f, 1.0f)
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"Ice Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::IceGem), 0.002f, 1.0f)
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"Wind Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::WindGem), 0.002f, 1.0f)
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"Earth Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::EarthGem), 0.002f, 1.0f)
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"Fire Gem",
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::FireGem), 0.002f, 1.0f)
	));

	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto playerIdleLeft = AnimatedSprite(spriteRepository().getSheet(SpriteSheets::PlayerIdleLeft), playerSpriteFrameRate, playerSpriteScale);

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Product,
		"testItem3",
		playerIdleLeft
	));
}

void setupRecipeList() {
	auto bottleItem = itemRepository.get("Blue Slime");
	auto playerItem = itemRepository.get("testItem3");

	recipeBook.addRecipe({bottleItem, bottleItem}, playerItem);
}