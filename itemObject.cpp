#include "itemObject.hpp"
#include "interactionSignal.hpp"
#include "itemSignals.hpp"
#include "objectSignals.hpp"

ItemObject::ItemObject(int64_t id, vec2<float>& pos, std::shared_ptr<Item> item) :
	Object(id, pos, vec2(0.0f)),
	item_(item), 
	Interactable(vec2(-10.0f), vec2(item->sprite.getWidth(), item->sprite.getHeight()) + 10, false) 
{}

ItemObject::~ItemObject() {
	interactionSignalUnsub();
}

void ItemObject::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	item_->sprite.draw(surface, pos_.x + offset.x, pos_.y + offset.y + drawOffset);

	// Get item to bob up and down.
	if (drawOffset >= maxDrawOffset) drawOffsetStep = -0.5f;
	if (drawOffset <= minDrawOffset) drawOffsetStep = 0.5f;
	drawOffset += drawOffsetStep;
};

void ItemObject::subscribe() {
	unsubscribers.push_back(onInteractionStart.subscribe([this]() {
		interactionSignalUnsub = interactionSignal.subscribe([this]() {
			itemPickedUp.emit(item_);
			deleteObjectSignal.emit(getId());
		});
	}));

	unsubscribers.push_back(onInteractionEnd.subscribe([this]() {
		interactionSignalUnsub();
	}));
}