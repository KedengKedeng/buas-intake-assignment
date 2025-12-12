#include "inventorySlot.hpp"

InventorySlot::InventorySlot(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::shared_ptr<Item> item, std::function<void(Tmpl8::vec2&)> onDragEndHandler)
	: Object(id, pos, BoundingBox(Tmpl8::vec2(0), size), ObservableBoundingBox()), mouseMoveHandler_(){
	mouseMoveHandler_.setInteractionCheck([this](Tmpl8::vec2& pos) {
		return getAbsoluteBounds().isInBounds(BoundingBox(pos, Tmpl8::vec2(0)));
	});

	mouseMoveHandler_.setOnMouseDragStart([this]() {
		dragPos = pos_;
		dragging = true;
	});

	mouseMoveHandler_.setOnMouseDrag([this](Tmpl8::vec2& pos, Tmpl8::vec2& delta) {
		dragPos += delta;
	});

	mouseMoveHandler_.setOnMouseDragEnd([this, onDragEndHandler]() {
		onDragEndHandler(dragPos);
		dragging = false;
	});
}

void InventorySlot::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	Tmpl8::vec2 pos = dragging ? dragPos : pos_;
	auto size = boundingBox_.getSize();
	surface->Box(
		pos_.x,
		pos_.y,
		pos_.x + size.x,
		pos_.y + size.y,
		0x000000
	);

	if (item_ != nullptr) item_->sprite.drawScaled(
		surface, 
		pos.x + (size.x - item_->sprite.getWidth() / 2) / 2, 
		pos.y + (size.y - item_->sprite.getHeight() / 2) / 2,
		0.5f
	);
}

void InventorySlot::subscribe() {
	Object::subscribe();

	mouseMoveHandler_.subscribe();
}

void InventorySlot::unsubscribe() {
	Object::unsubscribe();

	mouseMoveHandler_.unsubscribe();
}