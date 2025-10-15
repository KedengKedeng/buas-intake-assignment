#include "player.hpp"
#include <algorithm>
#include <cmath>

void Player::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1.0f));

	Tmpl8::vec2 newPos = pos_ + velocity / sidewardsPenalty * delta_;

	if (newPos.x != pos_.x || newPos.y != pos_.y)
		requestMove.emit(pos_, newPos, *this);
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