#include "inventorySlot.hpp"
#include "text.hpp"
#include <format>

InventorySlot::InventorySlot(int64_t id, vec2<float>& pos, vec2<float>& size, std::shared_ptr<Item> item, int amount, std::function<void(InventorySlot*, vec2<float>&)> onDragEndHandler)
	: Object(id, pos, size), mouseMoveHandler_(){
	mouseMoveHandler_.setInteractionCheck([this](vec2<float>& pos) {
		return BoundingBox(pos_, size_).isInBounds(pos);
	});

	mouseMoveHandler_.setOnMouseDragStart([this]() {
		dragPos = pos_;
		dragging = true;
	});

	mouseMoveHandler_.setOnMouseDrag([this](vec2<float>& pos, vec2<float>& delta) {
		dragPos += delta;
	});

	mouseMoveHandler_.setOnMouseDragEnd([this, onDragEndHandler]() {
		onDragEndHandler(this, dragPos);
		dragging = false;
	});
}

void InventorySlot::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	vec2<float> pos = dragging ? dragPos : pos_;

	surface->Box(
		pos_.x,
		pos_.y,
		pos_.x + size_.x,
		pos_.y + size_.y,
		0x000000
	);

	if (item_ != nullptr) {
		item_->sprite.drawScaled(
			surface,
			pos.x + (size_.x - item_->sprite.getWidth() / 2) / 2,
			pos.y + (size_.y - item_->sprite.getHeight() / 2) / 2,
			0.5f
		);

		vec2 pos(pos_.x + 10, pos_.y + size_.y - 10);
		Text(std::format("x{}", amount_), 1, 0xffffff).draw(surface, pos);
	}
}

void InventorySlot::subscribe() {
	Object::subscribe();

	mouseMoveHandler_.subscribe();
}

void InventorySlot::unsubscribe() {
	Object::unsubscribe();

	mouseMoveHandler_.unsubscribe();
}