#include "blower.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

Blower::Blower(int64_t id, Tmpl8::vec2& pos) 
	: Object(id, pos, BoundingBox(), ObservableBoundingBox()), 
	mouseMoveHandler(), 
	sprites_(spriteRepository.getAnimated("blower", 0, 0.4f).getFrames())
{
	allowCollision = false;

	boundingBox_.setSize(Tmpl8::vec2(sprites_[0].getWidth(), sprites_[0].getHeight()));

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

void Blower::addBlowerPosition(float delta) { 
	float oldBlowerPos = blowerPosition;
	blowerPosition = std::min(std::max(blowerPosition + delta, 0.0f), 99.0f); 
	blowedSignal.emit(blowerPosition - oldBlowerPos);
};

void Blower::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	int frame = static_cast<int>(floor(blowerPosition / 25));
	sprites_[frame].draw(surface, pos_.x + offset.x, pos_.y + offset.y);
}

void Blower::process(float deltaTime) {
	// slowly bring blower back up if no interaction is happening
	if (inflate) addBlowerPosition(-0.5f);
}

void Blower::subscribe() {
	Object::subscribe();
	mouseMoveHandler.subscribe();
}

void Blower::unsubscribe() {
	Object::unsubscribe();
	mouseMoveHandler.unsubscribe();
}