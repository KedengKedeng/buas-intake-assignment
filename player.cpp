#include "player.hpp"
#include <algorithm>
#include <cmath>

void Player::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1.0f));

	int newX = x_ + static_cast<int>(velocity.x / sidewardsPenalty * delta_.x);
	int newY = y_ + static_cast<int>(velocity.y / sidewardsPenalty * delta_.y);

	if (newX != x_ || newY != y_)
		requestMove.emit(Tmpl8::vec2(x_, y_), Tmpl8::vec2(newX, newY), *this);
}

void Player::move(Tmpl8::vec2 newPos) {
	x_ = newPos.x;
	y_ = newPos.y;

	boundingBox_.setPos(Tmpl8::vec2(x_, y_));
}

void Player::draw(Tmpl8::Surface* surface) {
	sprite_.Draw(surface, x_, y_);
};

void Player::process() {
	calculateMove();
}