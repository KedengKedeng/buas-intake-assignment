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
		name(name), 
		price(price), 
		idleLeft(idleLeft), 
		idleRight(idleRight), 
		walkLeft(walkLeft), 
		walkRight(walkRight) 
	{ }

	std::string name;
	int price;
	AnimatedSprite idleLeft;
	AnimatedSprite idleRight;
	AnimatedSprite walkLeft;
	AnimatedSprite walkRight;
};