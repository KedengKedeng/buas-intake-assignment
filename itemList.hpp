#pragma once
#include "itemsRepository.hpp"
#include "spriteRepository.hpp"

void setupItemList() {
	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		0xffffff,
		2.5f,
		1.35f,
		"testItem",
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository.get("waterbottle", 0.3f) }), 20.0f, 1.0f)
	));

	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		0xffffff,
		2.5f,
		1.35f,
		"testItem2",
		AnimatedSprite(std::make_shared<SpriteSheet>(std::vector<Sprite>{ spriteRepository.get("waterbottle", 0.3f) }), 20.0f, 1.0f)
	));
}