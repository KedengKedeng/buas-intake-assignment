#include "itemObject.hpp"

void ItemObject::draw(Tmpl8::Surface* surface) {
	item_->sprite.Draw(surface, pos_.x, pos_.y + drawOffset);

	// Get item to bob up and down.
	if (drawOffset >= maxDrawOffset) drawOffsetStep = -0.5f;
	if (drawOffset <= minDrawOffset) drawOffsetStep = 0.5f;
	drawOffset += drawOffsetStep;
};