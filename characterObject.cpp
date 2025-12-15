#include "characterObject.hpp"
#include "objectSignals.hpp"

CharacterObject::CharacterObject(
	int64_t id,
	Tmpl8::vec2& pos,
	BoundingBox& boundingBox,
	ObservableBoundingBox& interactableBoundingBox,
	Sprite& idleLeft,
	Sprite& idleRight,
	Sprite& walkLeft,
	Sprite& walkRight
): SpriteObject(id, pos, boundingBox, interactableBoundingBox) {
	addSprite(idleLeft);
	addSprite(idleRight);
	addSprite(walkLeft);
	addSprite(walkRight);
}

void CharacterObject::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1.0f));

	Tmpl8::vec2 calculatedVelocity = velocity / sidewardsPenalty * delta_;

	requestMove.emit(pos_, calculatedVelocity, *this);
}

void CharacterObject::process() {
	calculateMove();
}

void CharacterObject::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	if (delta_.x || delta_.y) setSprite(static_cast<int>(lookingDirection_) + 2); // set to running animations
	else setSprite(static_cast<int>(lookingDirection_)); // set to idle animations

	SpriteObject::draw(surface, offset);
}