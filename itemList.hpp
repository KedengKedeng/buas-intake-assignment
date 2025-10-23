#pragma once
#include "itemsRepository.hpp"

void setupItemList() {
	itemRepository.insert(std::make_shared<Item>(
		ItemTypes::Animal,
		0xffffff,
		2.5f,
		1.35f,
		std::string("testItem"),
		Sprite(std::string("waterbottle"), 0.3f)
	));
}