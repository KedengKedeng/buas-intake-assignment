#pragma once
#include "item.hpp"
#include "object.hpp"
#include "mouseHandler.hpp"
#include "subscriptionManager.hpp"

class InventorySlot : public Object, public SubscriptionManager {
public:
	InventorySlot(
		int64_t id,
		vec2<float>& pos,
		vec2<float>& size,
		std::shared_ptr<Item> item,
		int amount,
		std::function<void(InventorySlot*, vec2<float>&)> onDragEndHandler
	);

	void setItem(std::shared_ptr<Item> item, int amount) { item_ = item; amount_ = amount; }
	std::shared_ptr<Item> getItem() { return item_; }

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	vec2<float> dragPos = { 0, 0 };
	bool dragging = false;

	MouseHandler mouseHandler_;
	std::shared_ptr<Item> item_;
	int amount_ = 0;
};