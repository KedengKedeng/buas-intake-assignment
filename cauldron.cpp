#include "cauldron.hpp"
#include "itemSignals.hpp"

Cauldron::Cauldron(int64_t id, Tmpl8::vec2 pos) :
	SpriteObject(
		id,
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(0)),
		ObservableBoundingBox(Tmpl8::vec2(-10), Tmpl8::vec2(0))
	) {
	sprites_.push_back(
		Sprite(std::string("emptycauldron"), 1)
	);

	boundingBox_.setSize(Tmpl8::vec2(sprites_[0].getWidth(), sprites_[0].getHeight()));
	interactionBoundingBox_.setSize(Tmpl8::vec2(sprites_[0].getWidth() + 10, sprites_[0].getHeight() + 10));
}

Cauldron::~Cauldron() {
	onInteractEnd();
}

void Cauldron::onInteractStart() {
	itemDroppedUnsub = itemDropped.subscribe([this](std::shared_ptr<Item> item) {
		items_.push_back(item);

		return true;
	});
}

void Cauldron::onInteractEnd() {
	itemDroppedUnsub();
}