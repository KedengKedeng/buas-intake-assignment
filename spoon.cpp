#include "spoon.hpp"

Spoon::Spoon(int64_t id, Tmpl8::vec2& pos) : SpriteObject(id, pos, BoundingBox(), ObservableBoundingBox()), mouseMoveHandler() {
	addSprite(Sprite(std::string("spoon"), 0.5));

	boundingBox_.setSize(Tmpl8::vec2(getWidth(), getHeight()));

	mouseMoveHandler.setInteractionCheck([this](Tmpl8::vec2& pos) {
		return getAbsoluteBounds().isInBounds(BoundingBox(pos, Tmpl8::vec2(0)));
	});

	mouseMoveHandler.setOnMouseDrag([this](Tmpl8::vec2& pos, Tmpl8::vec2& delta) {
		pos_ += delta;
	});
}

void Spoon::subscribe() {
	SpriteObject::subscribe();

	mouseMoveHandler.subscribe();
}

void Spoon::unsubscribe() {
	SpriteObject::unsubscribe();

	mouseMoveHandler.unsubscribe();
}