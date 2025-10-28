#include "itemObject.hpp"

ItemObject::ItemObject(Tmpl8::vec2 pos, std::string& itemName) :
	Object(pos, BoundingBox(), ObservableBoundingBox()), item_(itemRepository.get(itemName)) {
	interactionBoundingBox_ = ObservableBoundingBox(Tmpl8::vec2(-10, -10), Tmpl8::vec2(item_->sprite.getWidth() + 10, item_->sprite.getHeight() + 10));
	allowCollision = false;
}

void ItemObject::draw(Tmpl8::Surface* surface) {
	item_->sprite.draw(surface, pos_.x, pos_.y + drawOffset);

	// Get item to bob up and down.
	if (drawOffset >= maxDrawOffset) drawOffsetStep = -0.5f;
	if (drawOffset <= minDrawOffset) drawOffsetStep = 0.5f;
	drawOffset += drawOffsetStep;
};