#include "blower.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

Blower::Blower(int64_t id, vec2<float> pos) :
	Object(id, pos, vec2(0.0f)),
	sprites_(spriteRepository().getSheet(SpriteSheets::Blower))
{
	setSize(vec2<float>(sprites_->getWidth(), sprites_->getHeight()));
}

void Blower::addBlowerPosition(float delta) { 
	float oldBlowerPos = blowerPosition;
	blowerPosition = std::min(std::max(blowerPosition + delta, 0.0f), 99.0f); 
	blowedSignal.emit(blowerPosition - oldBlowerPos);
};

void Blower::onMouseDown(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseDown(pos, screenPos);

	inflate = false;
	blowerInteracted.emit();
}

void Blower::onMouseUp(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseUp(pos, screenPos);

	inflate = true;
	blowerInteractionEnded.emit();
}

void Blower::onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {
	Clickable::onMouseDrag(pos, screenPos, delta);

	if (!delta.y) return;
	addBlowerPosition(delta.y / (100 / getSize().y));
}

void Blower::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	int frame = static_cast<int>(floor(blowerPosition / 25));
	auto pos = getPos() + offset;
	sprites_->getSprite(frame).drawScaled(surface, pos.x, pos.y, 0.4f);
}

void Blower::process(float deltaTime) {
	// slowly bring blower back up if no interaction is happening
	if (inflate) addBlowerPosition(-0.5f);
}