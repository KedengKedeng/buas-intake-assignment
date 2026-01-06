#include "inventorySlot.hpp"
#include <format>

InventorySlot::InventorySlot(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::shared_ptr<Item> item, int amount, std::function<void(InventorySlot*, Tmpl8::vec2&)> onDragEndHandler)
	: Object(id, pos, size), mouseMoveHandler_(){
	mouseMoveHandler_.setInteractionCheck([this](Tmpl8::vec2& pos) {
		return BoundingBox(pos_, size_).isInBounds(BoundingBox(pos, Tmpl8::vec2(0)));
	});

	mouseMoveHandler_.setOnMouseDragStart([this]() {
		dragPos = pos_;
		dragging = true;
	});

	mouseMoveHandler_.setOnMouseDrag([this](Tmpl8::vec2& pos, Tmpl8::vec2& delta) {
		dragPos += delta;
	});

	mouseMoveHandler_.setOnMouseDragEnd([this, onDragEndHandler]() {
		onDragEndHandler(this, dragPos);
		dragging = false;
	});
}

void InventorySlot::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	Tmpl8::vec2 pos = dragging ? dragPos : pos_;

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

		Tmpl8::vec2 pos = Tmpl8::vec2(pos_.x + 10, pos_.y + size_.y - 10);
		surface->Print(const_cast<char*>(std::format("x{}", amount_).c_str()), pos.x, pos.y, 0xfffffff);
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