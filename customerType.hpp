#pragma once
#include "animatedSprite.hpp"
#include <string>

struct CustomerType {
	CustomerType(
		const std::string& name,
		const AnimatedSprite& idleLeft,
		const AnimatedSprite& idleRight,
		const AnimatedSprite& walkLeft,
		const AnimatedSprite& walkRight
	) :
		name(name),
		idleLeft(idleLeft),
		idleRight(idleRight),
		walkLeft(walkLeft),
		walkRight(walkRight)
	{}

	std::string name;
	AnimatedSprite idleLeft;
	AnimatedSprite idleRight;
	AnimatedSprite walkLeft;
	AnimatedSprite walkRight;
};