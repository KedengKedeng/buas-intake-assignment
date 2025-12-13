#pragma once
#include "item.hpp"
#include "object.hpp"
#include "mouseMoveHandler.hpp"

class InventorySlot : public Object {
public:
	InventorySlot(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::shared_ptr<Item> item, std::function<void(InventorySlot*, Tmpl8::vec2&)> onDragEndHandler);

	void setItem(std::shared_ptr<Item> item) { item_ = item; }
	std::shared_ptr<Item> getItem() { return item_; }

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	Tmpl8::vec2 dragPos = { 0, 0 };
	bool dragging = false;

	MouseMoveHandler mouseMoveHandler_;
	std::shared_ptr<Item> item_;
};