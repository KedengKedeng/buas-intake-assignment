#include "player.hpp"
#include <algorithm>
#include <cmath>

void Player::move() {
	// Make movement in each direction half speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta.x) + std::abs(delta.y), 1.0f));

	x_ += static_cast<int>(velocity.x / sidewardsPenalty * delta.x);
	y_ += static_cast<int>(velocity.y / sidewardsPenalty * delta.y);
}

void Player::process() {
	move();
}