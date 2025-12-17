#include "spoon.hpp"
#include "objectSignals.hpp"

Tmpl8::vec2 spoonVelocity = { 0, 7 };

Spoon::Spoon(int64_t id, Tmpl8::vec2& pos) : SpriteObject(id, pos, BoundingBox(), ObservableBoundingBox()), mouseMoveHandler() {
	addSprite(Sprite("spoon", 0.4));

	boundingBox_.setPos(Tmpl8::vec2(20));
	boundingBox_.setSize(Tmpl8::vec2(getWidth() - 40, getHeight() - 40));
	interactionBoundingBox_.setPos(Tmpl8::vec2(20));
	interactionBoundingBox_.setSize(Tmpl8::vec2(getWidth() - 40, getHeight() - 40));

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

void Spoon::process() {
	if (velocity.x || velocity.y) requestMove.emit(pos_, velocity, *this);
}

void Spoon::subscribe() {
	SpriteObject::subscribe();

	mouseMoveHandler.subscribe();
}

void Spoon::unsubscribe() {
	SpriteObject::unsubscribe();

	mouseMoveHandler.unsubscribe();
}