#include "inventorySlot.hpp"

InventorySlot::InventorySlot(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::shared_ptr<Item> item)
	: Container(id, pos, size, Justification::NONE){

}

void InventorySlot::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	auto size = boundingBox_.getSize();
	surface->Box(
		pos_.x,
		pos_.y,
		pos_.x + size.x,
		pos_.y + size.y,
		0x000000
	);

	if (item_ != nullptr) item_->sprite.draw(
		surface, 
		pos_.x + (size.x - item_->sprite.getWidth()) / 2, 
		pos_.y + (size.y - item_->sprite.getHeight()) / 2
	);
}