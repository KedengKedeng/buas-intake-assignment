#include "player.hpp"
#include "playerSignals.hpp"
#include <algorithm>
#include <cmath>
#include "spriteRepository.hpp"

const int playerInteractionOffset = 10;
const float playerSpriteScale = 2.5f;

Player::Player(int64_t id, Tmpl8::vec2 pos) :
	SpriteObject(
		id,
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(0)),
		ObservableBoundingBox(Tmpl8::vec2(-playerInteractionOffset), Tmpl8::vec2(0))
	) {
	sprites_.push_back(Sprite(std::string("playeridleleft"), playerSpriteScale));
	sprites_.push_back(Sprite(std::string("playeridleright"), playerSpriteScale));
	sprites_.push_back(Sprite(std::string("playerwalkleft"), playerSpriteScale));
	sprites_.push_back(Sprite(std::string("playerwalkright"), playerSpriteScale));

	boundingBox_.setSize(Tmpl8::vec2(sprites_[0].getWidth(), sprites_[0].getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(sprites_[0].getWidth() + playerInteractionOffset, sprites_[0].getHeight() + playerInteractionOffset));

	subscribe();
};

void Player::subscribe() {
	SpriteObject::subscribe();

	walkSignalUnsub = walkSignal.subscribe([this](Tmpl8::vec2& delta) {
		addDelta(delta);

		if (delta_.x < 0) lookDirection = 0;
		if (delta_.x > 0) lookDirection = 1;
	});
}

void Player::unsubscribe() {
	SpriteObject::unsubscribe();

	walkSignalUnsub();
}

void Player::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1.0f));

	Tmpl8::vec2 calculatedVelocity = velocity / sidewardsPenalty * delta_;

	requestMove.emit(pos_, calculatedVelocity, *this);
}

void Player::move(Tmpl8::vec2 newPos) {
	pos_ = newPos;
}

void Player::process() {
	calculateMove();
}

void Player::draw(Tmpl8::Surface* surface) {
	if (delta_.x || delta_.y) currentSprite_ = lookDirection + 2; // set to running animations
	else currentSprite_ = lookDirection; // set to idle animations

	SpriteObject::draw(surface);

	if (item_ != nullptr) {
		Tmpl8::vec2 playerSize = boundingBox_.getSize();
		float xPos = pos_.x + playerSize.x - (item_->sprite.getWidth() * 0.5f) / 3;
		float yPos = pos_.y + playerSize.y / 2 - (item_->sprite.getHeight() * 0.5f) / 2;
		item_->sprite.drawScaled(surface, xPos, yPos, 0.5f);
	}
}