#include "spoon.hpp"
#include "objectSignals.hpp"
#include "sprite.hpp"
#include "spriteRepository.hpp"

vec2<float> spoonVelocity( 0.0f, 7.0f );

Spoon::Spoon(int64_t id, vec2<float>& pos) : 
	Object(id, pos, vec2(0.0f)),
	Collider(),
	Interactable(vec2(0.0f), vec2(0.0f), true),
	mouseMoveHandler(), 
	sprite_(spriteRepository.get("spoon", 0.4)) 
{
	addCollider(BoundingBox(vec2(20.0f), vec2(sprite_.getWidth(), sprite_.getHeight()) - 40));
	interactionBox_.setPos(vec2(20.0f));
	interactionBox_.setSize(vec2(sprite_.getWidth(), sprite_.getHeight()) - 40);

	mouseMoveHandler.setInteractionCheck([this](vec2<float>& pos) {
		return interactionBox_.at(pos_).isInBounds(pos);
	});

	mouseMoveHandler.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		requestMove.emit(pos_, delta, *this);
	});

	mouseMoveHandler.setOnMouseDragStart([this]() {
		velocity = { 0, 0 };
	});

	mouseMoveHandler.setOnMouseDragEnd([this]() {
		velocity = spoonVelocity;
	});
}

void Spoon::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	sprite_.draw(surface, pos_.x + offset.x, pos_.y + offset.y);
}

void Spoon::process(float deltaTime) {
	if (velocity.x || velocity.y) requestMove.emit(pos_, velocity, *this);
}

void Spoon::subscribe() {
	mouseMoveHandler.subscribe();
}

void Spoon::unsubscribe() {
	SubscriptionManager::unsubscribe();

	mouseMoveHandler.unsubscribe();
}