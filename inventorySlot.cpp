#include "inventorySlot.hpp"
#include "text.hpp"
#include "uiSignals.hpp"
#include <format>

InventorySlot::InventorySlot(
	int64_t id, 
	vec2<float> pos, 
	vec2<float> size, 
	std::shared_ptr<Item> item, 
	int amount, 
	std::function<void(InventorySlot*, vec2<float>)> onDragEndHandler
) : 
	Object(id, pos, size),
	onDragEndHandler_(onDragEndHandler)
{}

void InventorySlot::onMouseDown(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseDown(pos, screenPos);

	dragPos = screenPos;
	dragging = true;

	drawOnTop.emit(getId(), [this](Tmpl8::Surface* surface, vec2<float> offset) {
		if (item_ == nullptr) return;

		vec2 itemPos = dragPos + offset + (getSize() - vec2(item_->sprite.getWidth(), item_->sprite.getHeight()) / 2) / 2;
		item_->sprite.drawScaled(surface, itemPos.x, itemPos.y, 0.5f);
	});
};

void InventorySlot::onMouseUp(vec2<float> pos, vec2<float> screenPos) {
	Clickable::onMouseUp(pos, screenPos);

	onDragEndHandler_(this, dragPos);
	dragging = false;
	removeDrawOnTop.emit(getId());
};

void InventorySlot::onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {
	Clickable::onMouseDrag(pos, screenPos, delta);

	dragPos += delta;
};

void InventorySlot::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	auto pos = getPos() + offset;
	auto size = getSize();

	surface->Box(pos, pos + size, 0xff000000);

	if (item_ != nullptr && !dragging) {
		vec2 itemPos = pos + (size - vec2(item_->sprite.getWidth(), item_->sprite.getHeight()) / 2) / 2;
		item_->sprite.drawScaled(surface, itemPos.x, itemPos.y, 0.5f);
		Text(std::format("x{}", amount_), 1, 0xffffffff).draw(surface, vec2(pos.x + 10, pos.y + size.y - 10));
	}
}