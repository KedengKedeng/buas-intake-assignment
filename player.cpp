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
		Tmpl8::vec2(0),
		ObservableBoundingBox(Tmpl8::vec2(-playerInteractionOffset), Tmpl8::vec2(0)),
		spriteRepository.getAnimated("playeridleleft", playerSpriteFrameRate, playerSpriteScale),
		spriteRepository.getAnimated("playeridleright", playerSpriteFrameRate, playerSpriteScale),
		spriteRepository.getAnimated("playerwalkleft", playerSpriteFrameRate, playerSpriteScale),
		spriteRepository.getAnimated("playerwalkright", playerSpriteFrameRate, playerSpriteScale)
	) {
	collidingBox_.setSize(Tmpl8::vec2(getTextureWidth(), getTextureHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(getTextureWidth() + playerInteractionOffset * 2, getTextureHeight() + playerInteractionOffset * 2));
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