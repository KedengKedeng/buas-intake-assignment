#include "player.hpp"
#include "playerSignals.hpp"
#include "objectSignals.hpp"
#include <algorithm>
#include <cmath>
#include "spriteRepository.hpp"

const int playerInteractionOffset = 10;
const float playerSpriteScale = 2.5f;

Player::Player(int64_t id, Tmpl8::vec2& pos) :
	SpriteObject(
		id,
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(0)),
		ObservableBoundingBox(Tmpl8::vec2(-playerInteractionOffset), Tmpl8::vec2(0))
	) {
	Sprite sprite = Sprite(std::string("playeridleleft"), playerSpriteScale);

	addSprite(sprite);
	addSprite(Sprite(std::string("playeridleright"), playerSpriteScale));
	addSprite(Sprite(std::string("playerwalkleft"), playerSpriteScale));
	addSprite(Sprite(std::string("playerwalkright"), playerSpriteScale));

	boundingBox_.setSize(Tmpl8::vec2(sprite.getWidth(), sprite.getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(sprite.getWidth() + playerInteractionOffset, sprite.getHeight() + playerInteractionOffset));
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

void Player::process() {
	calculateMove();
}

void Player::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	if (delta_.x || delta_.y) setSprite(lookDirection + 2); // set to running animations
	else setSprite(lookDirection); // set to idle animations

	SpriteObject::draw(surface, offset);
}