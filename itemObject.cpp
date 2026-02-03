#include "itemObject.hpp"
#include "interactionSignal.hpp"
#include "itemSignals.hpp"
#include "objectSignals.hpp"

ItemObject::ItemObject(int64_t id, vec2<float>& pos, std::shared_ptr<Item> item) :
	Object(id, pos, vec2(0.0f)),
	item_(item), 
	Interactable(vec2(-10.0f), vec2(item->sprite.getWidth(), item->sprite.getHeight()) + 10, false) 
{}

void ItemObject::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	item_->sprite.draw(surface, pos.x, pos.y + drawOffset);
};

void ItemObject::process(float deltaTime) {
	// Get item to bob up and down.
	if (drawOffset >= maxDrawOffset) drawOffsetStep = -0.5f;
	if (drawOffset <= minDrawOffset) drawOffsetStep = 0.5f;
	drawOffset += drawOffsetStep;
}

void ItemObject::subscribe() {
	addSubscription(interactionSignal.subscribe([this]() {
		if (!isInteracting) return;
		itemPickedUp.emit(item_);
		deleteObjectSignal.emit(getId());
	}));
}