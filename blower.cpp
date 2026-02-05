#include "blower.hpp"
#include "objectSignals.hpp"
#include "spriteRepository.hpp"

Blower::Blower(int64_t id, vec2<float> pos) :
	Object(id, pos, vec2(0.0f)),
	Interactable(),
	SubscriptionManager(),
	mouseHandler_(), 
	sprites_(spriteRepository().getSheet(SpriteSheets::Blower))
{
	interactionBox_.setSize(vec2<float>(sprites_->getWidth(), sprites_->getHeight()));

	mouseHandler_.setInteractionCheck([this](vec2<float> pos) {
		return getInteractableBoundsAt(getPos()).isInBounds(pos);
	});

	mouseHandler_.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		if (!delta.y) return;
		addBlowerPosition(delta.y / (100 / getInteractableSize().y));
	});

	mouseHandler_.setOnMouseDown([this]() {
		inflate = false;
		blowerInteracted.emit();
	});

	mouseHandler_.setOnMouseUp([this]() {
		inflate = true;
		blowerInteractionEnded.emit();
	});
}

void Blower::addBlowerPosition(float delta) { 
	float oldBlowerPos = blowerPosition;
	blowerPosition = std::min(std::max(blowerPosition + delta, 0.0f), 99.0f); 
	blowedSignal.emit(blowerPosition - oldBlowerPos);
};

void Blower::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	int frame = static_cast<int>(floor(blowerPosition / 25));
	auto pos = getPos() + offset;
	sprites_->getSprite(frame).drawScaled(surface, pos.x, pos.y, 0.4f);
}

void Blower::process(float deltaTime) {
	// slowly bring blower back up if no interaction is happening
	if (inflate) addBlowerPosition(-0.5f);
}

void Blower::subscribe() {
	mouseHandler_.subscribe();
}

void Blower::unsubscribe() {
	SubscriptionManager::unsubscribe();
	mouseHandler_.unsubscribe();
}