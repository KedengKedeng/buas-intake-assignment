#include "spoon.hpp"
#include "objectSignals.hpp"
#include "sprite.hpp"
#include "spriteRepository.hpp"

vec2<float> spoonVelocity( 0.0f, 7.0f );

Spoon::Spoon(int64_t id, vec2<float> pos) : 
	Object(id, pos, vec2(0.0f)),
	Collider(),
	Interactable(vec2(0.0f), vec2(0.0f), true),
	sprite_(spriteRepository().get(Sprites::Spoon, 0.4))
{
	auto size = vec2<float>(sprite_.getWidth(), sprite_.getHeight());
	setSize(size);
	addCollider(BoundingBox(vec2(0.0f), size));
	interactionBox_.setSize(size);
}

void Spoon::onMouseDown(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseDown(pos, screenPos);

	velocity = { 0, 0 };
};

void Spoon::onMouseUp(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseUp(pos, screenPos);

	velocity = spoonVelocity;
};

void Spoon::onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {
	Clickable::onMouseDrag(pos, screenPos, delta);

	requestMove.emit(getPos(), delta, *this);
};

void Spoon::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	sprite_.draw(surface, pos.x, pos.y);
}

void Spoon::process(float deltaTime) {
	if (velocity.x || velocity.y) requestMove.emit(getPos(), velocity, *this);
}