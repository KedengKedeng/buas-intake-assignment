#pragma once
#include "screen.hpp"
#include "inventory.hpp"

class InventoryScreen : public Screen {
public:
	InventoryScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override;
private:
	int drawRows = 0;
	int maxItemsOnRow = 9;
	vec2<float> inventorySlotSize = { 30.0f, 30.0f };
	std::shared_ptr<Inventory> inventory_;
};