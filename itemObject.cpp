#include "itemObject.hpp"
#include "interactionSignal.hpp"
#include "itemSignals.hpp"
#include "objectSignals.hpp"

ItemObject::ItemObject(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Item> item) :
	Object(id, pos, Tmpl8::vec2(0)),
	item_(item), 
	Interactable(Tmpl8::vec2(-10), Tmpl8::vec2(item->sprite.getWidth(), item->sprite.getHeight()) + 10, false) 
{}

ItemObject::~ItemObject() {
	interactionSignalUnsub();
}

void ItemObject::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
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