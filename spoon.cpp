#include "spoon.hpp"
#include "objectSignals.hpp"
#include "sprite.hpp"
#include "spriteRepository.hpp"

vec2<float> spoonVelocity( 0.0f, 7.0f );

Spoon::Spoon(int64_t id, vec2<float>& pos) : 
	Object(id, pos, vec2(0.0f)),
	Collider(),
	Interactable(vec2(0.0f), vec2(0.0f), true),
	mouseHandler(), 
	sprite_(spriteRepository.get("spoon", 0.4)) 
{
	addCollider(BoundingBox(vec2(20.0f), vec2(sprite_.getWidth(), sprite_.getHeight()) - 40));
	interactionBox_.setPos(vec2(20.0f));
	interactionBox_.setSize(vec2(sprite_.getWidth(), sprite_.getHeight()) - 40);

	mouseHandler.setInteractionCheck([this](vec2<float>& pos) {
		return interactionBox_.at(getPos()).isInBounds(pos);
	});

	mouseHandler.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		requestMove.emit(getPos(), delta, *this);
	});

	mouseHandler.setOnMouseDown([this]() {
		velocity = { 0, 0 };
	});

	mouseHandler.setOnMouseUp([this]() {
		velocity = spoonVelocity;
	});
}

void Spoon::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	sprite_.draw(surface, pos.x, pos.y);
}

void Spoon::process(float deltaTime) {
	if (velocity.x || velocity.y) requestMove.emit(getPos(), velocity, *this);
}

void Spoon::subscribe() {
	mouseHandler.subscribe();
}

void Spoon::unsubscribe() {
	SubscriptionManager::unsubscribe();

	mouseHandler.unsubscribe();
}