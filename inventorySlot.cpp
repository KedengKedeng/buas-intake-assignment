#include "inventorySlot.hpp"
#include "text.hpp"
#include "boundingBox.hpp"
#include <format>

InventorySlot::InventorySlot(int64_t id, vec2<float>& pos, vec2<float>& size, std::shared_ptr<Item> item, int amount, std::function<void(InventorySlot*, vec2<float>&)> onDragEndHandler)
	: Object(id, pos, size), mouseHandler_(){
	mouseHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(pos_, size_).isInBounds(pos);
	});

	mouseHandler_.setOnMouseDown([this]() {
		dragPos = pos_;
		dragging = true;
	});

	mouseHandler_.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		dragPos += delta;
	});

	mouseHandler_.setOnMouseUp([this, onDragEndHandler]() {
		onDragEndHandler(this, dragPos);
		dragging = false;
	});
}

void InventorySlot::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	vec2 pos = pos_ + offset;
	vec2 itemPos = dragging ? dragPos + offset : pos;

	surface->Box(pos, pos + size_, 0xff000000);

	if (item_ != nullptr) {
		item_->sprite.drawScaled(
			surface,
			itemPos.x + (size_.x - item_->sprite.getWidth() / 2) / 2,
			itemPos.y + (size_.y - item_->sprite.getHeight() / 2) / 2,
			0.5f
		);

		Text(std::format("x{}", amount_), 1, 0xffffffff).draw(surface, vec2(pos.x + 10, pos.y + size_.y - 10));
	}
}

void InventorySlot::subscribe() {
	mouseHandler_.subscribe();
}

void InventorySlot::unsubscribe() {
	mouseHandler_.unsubscribe();
}