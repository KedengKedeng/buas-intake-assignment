#include "spoon.hpp"
#include "objectSignals.hpp"
#include "sprite.hpp"
#include "spriteRepository.hpp"

Tmpl8::vec2 spoonVelocity = { 0, 7 };

Spoon::Spoon(int64_t id, Tmpl8::vec2& pos) : 
	Object(id, pos, Tmpl8::vec2(0)),
	Collider(),
	Interactable(),
	mouseMoveHandler(), 
	sprite_(spriteRepository.get("spoon", 0.4)) 
{
	collidingBox_.setPos(Tmpl8::vec2(20));
	collidingBox_.setSize(Tmpl8::vec2(sprite_.getWidth(), sprite_.getHeight()) - 40);
	interactionBox_.setPos(Tmpl8::vec2(20));
	interactionBox_.setSize(Tmpl8::vec2(sprite_.getWidth(), sprite_.getHeight()) - 40);

	mouseMoveHandler.setInteractionCheck([this](Tmpl8::vec2& pos) {
		return collidingBox_.at(pos_).isInBounds(pos);
	});

	mouseMoveHandler.setOnMouseDrag([this](Tmpl8::vec2& pos, Tmpl8::vec2& delta) {
		requestMove.emit(pos_, delta, *this);
	});

	mouseMoveHandler.setOnMouseDragStart([this]() {
		velocity = { 0, 0 };
	});

	mouseMoveHandler.setOnMouseDragEnd([this]() {
		velocity = spoonVelocity;
	});
}

void Spoon::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	sprite_.draw(surface, pos_.x + offset.x, pos_.y + offset.y);
}

void Spoon::process(float deltaTime) {
	if (velocity.x || velocity.y) requestMove.emit(pos_, velocity, *this);
}

void Spoon::subscribe() {
	Object::subscribe();

	mouseMoveHandler.subscribe();
}

void Spoon::unsubscribe() {
	Object::unsubscribe();

	mouseMoveHandler.unsubscribe();
}