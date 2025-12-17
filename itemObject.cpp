#include "itemObject.hpp"
#include "interactionSignal.hpp"
#include "itemSignals.hpp"
#include "objectSignals.hpp"

ItemObject::ItemObject(int64_t id, Tmpl8::vec2& pos, std::shared_ptr<Item> item) :
	Object(id, pos, BoundingBox(), ObservableBoundingBox()), item_(item) {
	interactionBoundingBox_.setPos(Tmpl8::vec2(-10));
	interactionBoundingBox_.setSize(Tmpl8::vec2(item_->sprite.getWidth() + 10, item_->sprite.getHeight() + 10));
	allowCollision = false;
}

ItemObject::~ItemObject() {
	onInteractEnd();
}

void ItemObject::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	item_->sprite.draw(surface, pos_.x + offset.x, pos_.y + offset.y + drawOffset);

	// Get item to bob up and down.
	if (drawOffset >= maxDrawOffset) drawOffsetStep = -0.5f;
	if (drawOffset <= minDrawOffset) drawOffsetStep = 0.5f;
	drawOffset += drawOffsetStep;
};

void ItemObject::onInteractStart() {
	interactionSignalUnsub = interactionSignal.subscribe([this]() {
		itemPickedUp.emit(item_);
		deleteObjectSignal.emit(getId());
	});
}

void ItemObject::onInteractEnd() {
	interactionSignalUnsub();
}