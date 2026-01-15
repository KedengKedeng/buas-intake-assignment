#include "characterObject.hpp"
#include "objectSignals.hpp"

CharacterObject::CharacterObject(
	int64_t id,
	vec2<float>& pos,
	vec2<float>& size,
	AnimatedSprite& idleLeft,
	AnimatedSprite& idleRight,
	AnimatedSprite& walkLeft,
	AnimatedSprite& walkRight,
	bool isInteractor
) : 
	Object(id, pos, size), 
	Collider(vec2<float>(0.0f), size),
	Interactable(vec2<float>(-10.0f), size + 10, isInteractor),
	sprites_(std::vector<AnimatedSprite>({idleLeft, idleRight, walkLeft, walkRight}))
{}

void CharacterObject::calculateMove() {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(static_cast<float>(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1)));

	vec2<float> calculatedVelocity = velocity / sidewardsPenalty * delta_;

	requestMove.emit(pos_, calculatedVelocity, *this);
}

void CharacterObject::process(float deltaTime) {
	sprites_.process(deltaTime);
	calculateMove();
}

void CharacterObject::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	if (delta_.x || delta_.y) sprites_.setSprite(static_cast<int>(lookingDirection_) + 2); // set to running animations
	else sprites_.setSprite(static_cast<int>(lookingDirection_)); // set to idle animations

	sprites_.draw(surface, pos_.x + offset.x, pos_.y + offset.y);
}