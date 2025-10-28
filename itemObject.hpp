#pragma once
#include "object.hpp"
#include "itemsRepository.hpp"

class ItemObject : public Object {
public:
	ItemObject(Tmpl8::vec2 pos, std::string itemName) : 
		Object(pos, BoundingBox(), ObservableBoundingBox()), item_(itemRepository.get(itemName)) {
		interactionBoundingBox_ = ObservableBoundingBox(Tmpl8::vec2(-10, -10), Tmpl8::vec2(item_->sprite.getWidth() + 10, item_->sprite.getHeight() + 10));
		allowCollision = false;
	}

	void draw(Tmpl8::Surface* surface);
	void process() override {};
private:
	std::shared_ptr<Item> item_;

	// TODO: randomize?
	float drawOffset = 0;
	float minDrawOffset = 0;
	float maxDrawOffset = 20;
	float drawOffsetStep = 0.5f;
};