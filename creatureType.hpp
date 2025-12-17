#pragma once
#include "animatedSprite.hpp"
#include <string>

struct CreatureType {
	CreatureType(
		const std::string& name, 
		int price, 
		const AnimatedSprite& idleLeft, 
		const AnimatedSprite& idleRight, 
		const AnimatedSprite& walkLeft, 
		const AnimatedSprite& walkRight
	) :
		name(std::move(name)), 
		price(price), 
		idleLeft(std::move(idleLeft)), 
		idleRight(std::move(idleRight)), 
		walkLeft(std::move(walkLeft)), 
		walkRight(std::move(walkRight)) 
	{ }

	std::string name;
	int price;
	AnimatedSprite idleLeft;
	AnimatedSprite idleRight;
	AnimatedSprite walkLeft;
	AnimatedSprite walkRight;
};