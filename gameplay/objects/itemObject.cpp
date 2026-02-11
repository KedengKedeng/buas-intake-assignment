#include "itemObject.hpp"
#include "interactionSignal.hpp"
#include "itemSignals.hpp"
#include "objectSignals.hpp"

ItemObject::ItemObject(int64_t id, vec2<float> pos, std::shared_ptr<Item> item) :
	Object(id, pos, vec2(0.0f)),
	Interactable(vec2(-10.0f), vec2(item->sprite.getWidth(), item->sprite.getHeight()) + 10, false),
	item_(item),
	itemSprite(item->sprite)
{}

void ItemObject::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	itemSprite.drawScaled(surface, pos.x, pos.y + drawOffset, 3.0f);
};

void ItemObject::process(float deltaTime) {
	// Get item to bob up and down.
	if (drawOffset >= maxDrawOffset) drawOffsetStep = -0.5f;
	if (drawOffset <= minDrawOffset) drawOffsetStep = 0.5f;
	drawOffset += drawOffsetStep;

	itemSprite.process(deltaTime);
}

void ItemObject::subscribe() {
	addSubscription(interactionSignal.subscribe([this]() {
		if (!isInteracting) return;
		itemPickedUp.emit(item_);
		deleteObjectSignal.emit(getId());
	}));
}