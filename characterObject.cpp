#include "characterObject.hpp"
#include "objectSignals.hpp"

CharacterObject::CharacterObject(
	int64_t id,
	Tmpl8::vec2& pos,
	Tmpl8::vec2& size,
	ObservableBoundingBox& interactableBoundingBox,
	AnimatedSprite& idleLeft,
	AnimatedSprite& idleRight,
	AnimatedSprite& walkLeft,
	AnimatedSprite& walkRight
) : 
	Object(id, pos, interactableBoundingBox), 
	Collider(Tmpl8::vec2(0), size),
	sprites_(std::vector<AnimatedSprite>({idleLeft, idleRight, walkLeft, walkRight}))
{}

void CharacterObject::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1.0f));

	Tmpl8::vec2 calculatedVelocity = velocity / sidewardsPenalty * delta_;

	requestMove.emit(pos_, calculatedVelocity, *this);
}

void CharacterObject::process(float deltaTime) {
	sprites_.process(deltaTime);
	calculateMove();
}

void CharacterObject::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	if (delta_.x || delta_.y) sprites_.setSprite(static_cast<int>(lookingDirection_) + 2); // set to running animations
	else sprites_.setSprite(static_cast<int>(lookingDirection_)); // set to idle animations

	sprites_.draw(surface, pos_.x + offset.x, pos_.y + offset.y);
}