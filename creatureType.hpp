#pragma once
#include "animatedSprite.hpp"
#include "item.hpp"
#include <string>

struct CreatureType {
	CreatureType(
		const std::string& name, 
		int price, 
		std::shared_ptr<Item> producedItem,
		float timeToProduce,
		const AnimatedSprite& idleLeft, 
		const AnimatedSprite& idleRight, 
		const AnimatedSprite& walkLeft, 
		const AnimatedSprite& walkRight
	) :
		name(name), 
		price(price), 
		producedItem(producedItem),
		timeToProduce(timeToProduce),
		idleLeft(idleLeft), 
		idleRight(idleRight), 
		walkLeft(walkLeft), 
		walkRight(walkRight) 
	{ }

	std::string name;
	int price;
	std::shared_ptr<Item> producedItem;
	float timeToProduce;
	AnimatedSprite idleLeft;
	AnimatedSprite idleRight;
	AnimatedSprite walkLeft;
	AnimatedSprite walkRight;
};