#pragma once
#include "animatedSprite.hpp"
#include "customerTypes.hpp"
#include <string>

struct CustomerType {
	CustomerType(
		CustomerTypes id,
		const std::string& name,
		const AnimatedSprite& idleLeft,
		const AnimatedSprite& idleRight,
		const AnimatedSprite& walkLeft,
		const AnimatedSprite& walkRight
	) :
		id(id),
		name(name),
		idleLeft(idleLeft),
		idleRight(idleRight),
		walkLeft(walkLeft),
		walkRight(walkRight)
	{}

	CustomerTypes id;
	std::string name;
	AnimatedSprite idleLeft;
	AnimatedSprite idleRight;
	AnimatedSprite walkLeft;
	AnimatedSprite walkRight;
};