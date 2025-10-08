#include "player.hpp"

void Player::move() {
	x_ += velocity.x;
	y_ += velocity.y;
}

void Player::process() {
	move();
}