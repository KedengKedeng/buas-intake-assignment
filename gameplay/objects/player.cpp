#include "player.hpp"
#include "playerSignals.hpp"
#include "spriteRepository.hpp"

const float playerInteractionOffset = 10.0f;
const float playerSpriteScale = 2.5f;
const float playerSpriteFrameRate = 0.005f;

Player::Player(int64_t id, vec2<float> pos) :
	CharacterObject(
		id,
		pos,
		vec2(0.0f),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::PlayerIdleLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::PlayerIdleRight), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::PlayerWalkLeft), playerSpriteFrameRate, playerSpriteScale),
		AnimatedSprite(spriteRepository().getSheet(SpriteSheets::PlayerWalkRight), playerSpriteFrameRate, playerSpriteScale),
		true
	) {
	addCollider(BoundingBox(vec2(0.0f), vec2(getTextureWidth(), getTextureHeight())));
	interactionBox_.setPos(vec2(-playerInteractionOffset));
	interactionBox_.setSize(vec2(getTextureWidth() + playerInteractionOffset * 2, getTextureHeight() + playerInteractionOffset * 2));
};

void Player::subscribe() {
	addSubscription(walkSignal.subscribe([this](vec2<int8_t> delta) {
		addDelta(delta);

		auto newDelta = getDelta();

		if (newDelta.x < 0) setLookingDirection(LookingDirections::LEFT);
		if (newDelta.x > 0) setLookingDirection(LookingDirections::RIGHT);
	}));
}