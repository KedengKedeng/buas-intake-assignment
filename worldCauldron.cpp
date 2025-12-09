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
	Sprite sprite = Sprite(std::string("emptycauldron"), 2.5);

	addSprite(sprite);
	addSprite(Sprite(std::string("filledcauldron"), 2.5));

	boundingBox_.setSize(Tmpl8::vec2(sprite.getWidth(), sprite.getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(sprite.getWidth() + 10, sprite.getHeight() + 10));
	pos_ = Tmpl8::vec2(pos_.x - sprite.getWidth() / 2, pos_.y - sprite.getHeight() / 2);
}

WorldCauldron::~WorldCauldron() {
	onInteractEnd();
}

void WorldCauldron::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	setSprite(cauldron_->getItemCount() != 0);

	SpriteObject::draw(surface, offset);
}

void WorldCauldron::subscribe() {
	SpriteObject::subscribe();

	interactionSignalUnsub = interactionSignal.subscribe([this]() {
		if (allowCauldronScreen && isInteracting) cauldronInteracted.emit();
	});

	itemPickedUpUnsub = itemPickedUp.subscribe([this](std::shared_ptr<Item>& item) {
		allowCauldronScreen = false;
	});
}

void WorldCauldron::unsubscribe() {
	SpriteObject::unsubscribe();

	interactionSignalUnsub();
	itemPickedUpUnsub();
}

void WorldCauldron::onInteractStart() {
	isInteracting = true;

	itemDroppedUnsub = itemDropped.subscribe([this](std::shared_ptr<Item> item) {
		cauldron_->insertItem(item);

		allowCauldronScreen = true;

		return true;
	});
}

void WorldCauldron::onInteractEnd() {
	isInteracting = false;

	itemDroppedUnsub();
}