#include "spoon.hpp"
#include "objectSignals.hpp"
#include "sprite.hpp"
#include "spriteRepository.hpp"

Tmpl8::vec2 spoonVelocity = { 0, 7 };

Spoon::Spoon(int64_t id, Tmpl8::vec2& pos) 
	: Object(id, pos, BoundingBox(), ObservableBoundingBox()), mouseMoveHandler(), sprite_(spriteRepository.get("spoon"), 0.4) {
	boundingBox_.setPos(Tmpl8::vec2(20));
	boundingBox_.setSize(Tmpl8::vec2(sprite_.getWidth() - 40, sprite_.getHeight() - 40));
	interactionBoundingBox_.setPos(Tmpl8::vec2(20));
	interactionBoundingBox_.setSize(Tmpl8::vec2(sprite_.getWidth() - 40, sprite_.getHeight() - 40));

	mouseMoveHandler.setInteractionCheck([this](Tmpl8::vec2& pos) {
		return getAbsoluteBounds().isInBounds(BoundingBox(pos, Tmpl8::vec2(0)));
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