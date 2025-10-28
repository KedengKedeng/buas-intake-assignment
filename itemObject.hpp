#pragma once
#include "object.hpp"
#include "itemsRepository.hpp"

class ItemObject : public Object {
public:
	ItemObject(Tmpl8::vec2 pos, std::string& itemName);

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