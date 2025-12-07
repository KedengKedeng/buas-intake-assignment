#include "blower.hpp"
#include "objectSignals.hpp"

Blower::Blower(int64_t id, Tmpl8::vec2& pos) 
	: SpriteObject(id, pos, BoundingBox(), ObservableBoundingBox()), mouseMoveHandler(){
	allowCollision = false;

	addSprite(Sprite(std::string("blower"), 0.4));

	boundingBox_.setSize(Tmpl8::vec2(getWidth(), getHeight()));

	mouseMoveHandler.setInteractionCheck([this](Tmpl8::vec2& pos) {
		return getAbsoluteBounds().isInBounds(BoundingBox(pos, Tmpl8::vec2(0)));
	});

	mouseMoveHandler.setOnMouseDrag([this](Tmpl8::vec2& pos, Tmpl8::vec2& delta) {
		if (!delta.y) return;
		addBlowerPosition(delta.y / (100 / boundingBox_.getSize().y));
	});

	mouseMoveHandler.setOnMouseDragStart([this]() {
		inflate = false;
		blowerInteracted.emit();
	});

	mouseMoveHandler.setOnMouseDragEnd([this]() {
		inflate = true;
		blowerInteractionEnded.emit();
	});
}

Blower::~Blower() {

}

void Blower::addBlowerPosition(float delta) { 
	float oldBlowerPos = blowerPosition;
	blowerPosition = std::min(std::max(blowerPosition + delta, 0.0f), 99.0f); 
	blowedSignal.emit(blowerPosition - oldBlowerPos);
};

void Blower::draw(Tmpl8::Surface* surface) {
	setFrame(static_cast<int>(floor(blowerPosition / 25)));
	drawNoAnimate(surface, pos_);
}

void Blower::process() {
	if (inflate) addBlowerPosition(-0.5f);
}

void Blower::subscribe() {
	SpriteObject::subscribe();
	mouseMoveHandler.subscribe();
}

void Blower::unsubscribe() {
	SpriteObject::unsubscribe();
	mouseMoveHandler.unsubscribe();
}