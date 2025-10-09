#include "player.hpp"

void Player::move() {
	x_ += velocity.x * delta.x;
	y_ += velocity.y * delta.y;
}

void Player::process() {
	move();
}