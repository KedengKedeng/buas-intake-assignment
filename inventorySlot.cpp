#include "inventorySlot.hpp"
#include "text.hpp"
#include "boundingBox.hpp"
#include "uiSignals.hpp"
#include <format>

InventorySlot::InventorySlot(int64_t id, vec2<float>& pos, vec2<float>& size, std::shared_ptr<Item> item, int amount, std::function<void(InventorySlot*, vec2<float>&)> onDragEndHandler)
	: Object(id, pos, size), mouseHandler_(){
	mouseHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(getPos(), getSize()).isInBounds(pos);
	});

	mouseHandler_.setOnMouseDown([this]() {
		dragPos = getPos();
		dragging = true;

		drawOnTop.emit(getId(), [this](Tmpl8::Surface* surface, const vec2<float>& offset) {
			if (item_ == nullptr) return;

			vec2 itemPos = dragPos + offset + (getSize() - vec2(item_->sprite.getWidth(), item_->sprite.getHeight()) / 2) / 2;
			item_->sprite.drawScaled(surface, itemPos.x, itemPos.y, 0.5f);
		});
	});

	mouseHandler_.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		dragPos += delta;
	});

	mouseHandler_.setOnMouseUp([this, onDragEndHandler]() {
		onDragEndHandler(this, dragPos);
		dragging = false;
		removeDrawOnTop.emit(getId());
	});
}

void InventorySlot::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto pos = getPos() + offset;
	auto size = getSize();

	surface->Box(pos, pos + size, 0xff000000);

	if (item_ != nullptr && !dragging) {
		vec2 itemPos = pos + (size - vec2(item_->sprite.getWidth(), item_->sprite.getHeight()) / 2) / 2;
		item_->sprite.drawScaled(surface, itemPos.x, itemPos.y, 0.5f);
		Text(std::format("x{}", amount_), 1, 0xffffffff).draw(surface, vec2(pos.x + 10, pos.y + size.y - 10));
	}
}

void InventorySlot::subscribe() {
	mouseHandler_.subscribe();
}

void InventorySlot::unsubscribe() {
	mouseHandler_.unsubscribe();
}