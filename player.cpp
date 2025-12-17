#include "player.hpp"
#include "playerSignals.hpp"
#include "objectSignals.hpp"
#include <algorithm>
#include <cmath>
#include "spriteRepository.hpp"

const int playerInteractionOffset = 10;
const float playerSpriteScale = 2.5f;
const float playerSpriteFrameRate = 0.005f;

Player::Player(int64_t id, Tmpl8::vec2& pos) :
	CharacterObject(
		id,
		pos,
		BoundingBox(),
		ObservableBoundingBox(Tmpl8::vec2(-playerInteractionOffset), Tmpl8::vec2(0)),
		AnimatedSprite(Sprite(spriteRepository.get("playeridleleft"), playerSpriteScale), playerSpriteFrameRate),
		AnimatedSprite(Sprite(spriteRepository.get("playeridleright"), playerSpriteScale), playerSpriteFrameRate),
		AnimatedSprite(Sprite(spriteRepository.get("playerwalkleft"), playerSpriteScale), playerSpriteFrameRate),
		AnimatedSprite(Sprite(spriteRepository.get("playerwalkright"), playerSpriteScale), playerSpriteFrameRate)
	) {
	boundingBox_.setSize(Tmpl8::vec2(getWidth(), getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(getWidth() + playerInteractionOffset, getHeight() + playerInteractionOffset));
};

void Player::subscribe() {
	CharacterObject::subscribe();

	unsubscribers.push_back(walkSignal.subscribe([this](Tmpl8::vec2& delta) {
		addDelta(delta);

		Tmpl8::vec2 delta_ = getDelta();

		if (delta_.x < 0) setLookingDirection(LookingDirections::LEFT);
		if (delta_.x > 0) setLookingDirection(LookingDirections::RIGHT);
	}));
}