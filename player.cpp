#include "player.hpp"
#include "playerSignals.hpp"
#include <algorithm>
#include <cmath>

const int playerInteractionOffset = 10;

Player::Player(Sprite& sprite, Tmpl8::vec2 pos) :
	SpriteObject(
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(sprite.getWidth(), sprite.getHeight())),
		ObservableBoundingBox(Tmpl8::vec2(-playerInteractionOffset), Tmpl8::vec2(sprite.getWidth() + playerInteractionOffset, sprite.getHeight() + playerInteractionOffset)),
		sprite
	) {
	walkSignal.subscribe([this](Tmpl8::vec2& delta) {
		addDelta(delta);
		});
};

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

void Player::process() {
	calculateMove();
}