#include "player.hpp"
#include "playerSignals.hpp"
#include "objectSignals.hpp"
#include <algorithm>
#include <cmath>
#include "spriteRepository.hpp"

const int playerInteractionOffset = 10;
const float playerSpriteScale = 2.5f;

Player::Player(int64_t id, Tmpl8::vec2& pos) :
	CharacterObject(
		id,
		pos,
		BoundingBox(),
		ObservableBoundingBox(Tmpl8::vec2(-playerInteractionOffset), Tmpl8::vec2(0)),
		Sprite(std::string("playeridleleft"), playerSpriteScale),
		Sprite(std::string("playeridleright"), playerSpriteScale),
		Sprite(std::string("playerwalkleft"), playerSpriteScale),
		Sprite(std::string("playerwalkright"), playerSpriteScale)
	) {
	boundingBox_.setSize(Tmpl8::vec2(getWidth(), getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(getWidth() + playerInteractionOffset, getHeight() + playerInteractionOffset));
};

void Player::subscribe() {
	CharacterObject::subscribe();

	walkSignalUnsub = walkSignal.subscribe([this](Tmpl8::vec2& delta) {
		addDelta(delta);

		Tmpl8::vec2 delta_ = getDelta();

		if (delta_.x < 0) setLookingDirection(LookingDirections::LEFT);
		if (delta_.x > 0) setLookingDirection(LookingDirections::RIGHT);
	});
}

void Player::unsubscribe() {
	CharacterObject::unsubscribe();

	walkSignalUnsub();
}