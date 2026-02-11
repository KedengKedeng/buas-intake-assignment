#pragma once
#include "item.hpp"
#include "object.hpp"
#include "clickable.hpp"
#include "spriteRepository.hpp"
#include <functional>

class InventorySlot : public Object, public Clickable {
public:
	InventorySlot(
		int64_t id,
		vec2<float> pos,
		vec2<float> size,
		int amount,
		std::function<void(InventorySlot*, vec2<float>)> onDragEndHandler
	);

	void setItem(std::shared_ptr<Item> item, int amount);
	std::shared_ptr<Item> getItem() const { return item_; }

	void onMouseDown(vec2<float> pos, vec2<float> screenPos) override;
	void onMouseUp(vec2<float> pos, vec2<float> screenPos) override;
	void onMouseDrag(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) override;

	void draw(Tmpl8::Surface& surface, vec2<float> offset) const override;
	void process(float deltaTime) override;
private:
	std::function<void(InventorySlot*, vec2<float>)> onDragEndHandler_;

	vec2<float> dragPos = { 0, 0 };
	std::shared_ptr<Item> item_ = nullptr;
	// placeholder texture until item is set
	mutable std::shared_ptr<AnimatedSprite> itemSprite_ = nullptr;
	int amount_ = 0;
	bool dragging = false;
};