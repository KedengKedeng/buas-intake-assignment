#pragma once
#include "itemsRepository.hpp"
#include "spriteRepository.hpp"
#include "recipeBook.hpp"

void setupItemList() {
	auto bottleSprite = AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository.get("waterbottle", 0.3f) }), 20.0f, 1.0f);
	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"testItem",
		bottleSprite
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		"testItem2",
		bottleSprite
	));

	const float playerInteractionOffset = 10.0f;
	const float playerSpriteScale = 2;
	const float playerSpriteFrameRate = 0.005f;
	auto playerIdleLeft = AnimatedSprite(spriteRepository.getSheet("playeridleleft"), playerSpriteFrameRate, playerSpriteScale);

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Product,
		"testItem3",
		playerIdleLeft
	));
}

void setupRecipeList() {
	auto bottleItem = itemRepository.get("testItem2");
	auto playerItem = itemRepository.get("testItem3");

	recipeBook.addRecipe({bottleItem, bottleItem}, playerItem);
}