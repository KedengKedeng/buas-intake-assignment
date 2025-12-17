#include "worldCauldron.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "objectSignals.hpp"

WorldCauldron::WorldCauldron(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Cauldron> cauldron) :
	SpriteObject(
		id,
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(0)),
		ObservableBoundingBox(Tmpl8::vec2(-10), Tmpl8::vec2(0))
	),
	cauldron_(cauldron) {
	addSprite(Sprite("emptycauldron", 2.5));
	addSprite(Sprite("filledcauldron", 2.5));
	addSprite(Sprite("emptyburningcauldron", 2.5));
	addSprite(Sprite("filledburningcauldron", 2.5));

	boundingBox_.setSize(Tmpl8::vec2(getWidth(), getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(getWidth() + 10, getHeight() + 10));
	pos_ = Tmpl8::vec2(pos_.x - getWidth() / 2, pos_.y - getHeight() / 2);
}

WorldCauldron::~WorldCauldron() {
	onInteractEnd();
}

void WorldCauldron::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	int spriteNum = cauldron_->getItemCount() != 0;
	if (cauldron_->getTemp() > 200) spriteNum += 2;
	setSprite(spriteNum);

	SpriteObject::draw(surface, offset);
}

void WorldCauldron::subscribe() {
	SpriteObject::subscribe();

	unsubscribers.push_back(interactionSignal.subscribe([this]() {
		if (isInteracting) cauldronInteracted.emit();
	}));
}

void WorldCauldron::onInteractStart() {
	isInteracting = true;

	itemDroppedUnsub = itemDropped.subscribe([this](std::shared_ptr<Item> item) {
		cauldron_->insertItem(item);

		return true;
	});
}

void WorldCauldron::onInteractEnd() {
	isInteracting = false;

	itemDroppedUnsub();
}