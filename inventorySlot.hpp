#pragma once
#include "item.hpp"
#include "container.hpp"

class InventorySlot : public Container {
public:
	InventorySlot(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::shared_ptr<Item> item);

	void setItem(std::shared_ptr<Item> item) { item_ = item; }

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;
private:
	std::shared_ptr<Item> item_;
};