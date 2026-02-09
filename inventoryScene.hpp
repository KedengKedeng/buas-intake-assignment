#pragma once
#include "scene.hpp"
#include "inventory.hpp"

class InventoryScene : public Scene {
public:
	InventoryScene(int width, int height, std::shared_ptr<Inventory> inventory);

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
	void process(float deltaTime) override;
private:
	int drawRows = 0;
	int maxItemsOnRow = 9;
	vec2<float> inventorySlotSize = { 30.0f, 30.0f };
	std::shared_ptr<Inventory> inventory_;
};