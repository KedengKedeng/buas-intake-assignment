#include "player.hpp"
#include <algorithm>
#include <cmath>

void Player::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1.0f));

	Tmpl8::vec2 calculatedVelocity = velocity / sidewardsPenalty * delta_;

	if (calculatedVelocity.x != 0.0f || calculatedVelocity.y != 0.0f)
		requestMove.emit(pos_, calculatedVelocity, *this);
}

void Player::move(Tmpl8::vec2 newPos) {
	pos_ = newPos;
}

void Player::draw(Tmpl8::Surface* surface) {
	sprite_.Draw(surface, pos_.x, pos_.y);
};

void Player::process() {
	calculateMove();
}