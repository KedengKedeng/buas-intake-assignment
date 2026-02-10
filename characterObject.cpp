#include "characterObject.hpp"
#include "objectSignals.hpp"

CharacterObject::CharacterObject(
	int64_t id,
	vec2<float> pos,
	vec2<float> size,
	const AnimatedSprite& idleLeft,
	const AnimatedSprite& idleRight,
	const AnimatedSprite& walkLeft,
	const AnimatedSprite& walkRight,
	bool isInteractor
) : 
	Object(id, pos, size), 
	Collider(vec2(0.0f), size),
	Interactable(vec2(-10.0f), size + 10, isInteractor),
	sprites_(std::vector<AnimatedSprite>({idleLeft, idleRight, walkLeft, walkRight}))
{}

void CharacterObject::calculateMove(float deltaTime) {
	// Make movement in each direction a lower speed
	// when diagonal movement is detected.
	float sidewardsPenalty = std::sqrt(static_cast<float>(std::max(std::abs(delta_.x) + std::abs(delta_.y), 1)));

	vec2<float> calculatedVelocity = (velocity_ * deltaTime)  / sidewardsPenalty * delta_;

	requestMove.emit(getPos(), calculatedVelocity, *this);
}

void CharacterObject::process(float deltaTime) {
	sprites_.process(deltaTime);
	calculateMove(deltaTime);
}

void CharacterObject::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	if (delta_.x || delta_.y) sprites_.setSprite(static_cast<int>(lookingDirection_) + 2); // set to running animations
	else sprites_.setSprite(static_cast<int>(lookingDirection_)); // set to idle animations

	auto pos = getPos() + offset;
	sprites_.draw(surface, pos.x, pos.y);
	//drawColliders(surface, pos);
}