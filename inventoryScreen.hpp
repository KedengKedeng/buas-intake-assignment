#pragma once
#include "screen.hpp"
#include "inventory.hpp"

class InventoryScreen : public Screen {
public:
	InventoryScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory);

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;
	void process() override;
private:
	int drawRows = 0;
	int maxItemsOnRow = 9;
	Tmpl8::vec2 inventorySlotSize = { 30, 30 };
	std::shared_ptr<Inventory> inventory_;
};