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
		spriteRepository.get("waterbottle", 0.3f)
	));
}