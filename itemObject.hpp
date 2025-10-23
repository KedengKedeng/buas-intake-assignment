#pragma once
#include "object.hpp"
#include "itemsRepository.hpp"

class ItemObject : public Object {
public:
	ItemObject(Tmpl8::vec2 pos, std::string itemName) : 
		Object(pos, BoundingBox(Tmpl8::vec2(0,0), Tmpl8::vec2(0, 0))), item_(itemRepository.get(itemName)) {
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