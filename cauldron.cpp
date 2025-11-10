#include "cauldron.hpp"
#include "itemSignals.hpp"

Cauldron::Cauldron(int64_t id, Sprite& sprite, Tmpl8::vec2 pos) :
	SpriteObject(
		id,
		pos,
		BoundingBox(Tmpl8::vec2(0), Tmpl8::vec2(sprite.getWidth(), sprite.getHeight())),
		ObservableBoundingBox(Tmpl8::vec2(-10), Tmpl8::vec2(sprite.getWidth() + 10, sprite.getHeight() + 10)),
		sprite
	) {}

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