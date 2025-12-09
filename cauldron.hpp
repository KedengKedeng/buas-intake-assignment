#pragma once
#include "item.hpp"
#include "object.hpp"
#include <vector>

class Cauldron : public Object {
public:
	Cauldron(): Object(0, Tmpl8::vec2(0), BoundingBox(), ObservableBoundingBox()) {};

	void insertItem(std::shared_ptr<Item> item);
	size_t getItemCount() { return items_.size(); }

	void stir(float delta);
	void addTemp(float delta);
	float getTemp();

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override {};
private:
	float amountToStir = 0;
	float neededTemp = 0;
	float temp = 0;
	std::vector<std::shared_ptr<Item>> items_ = {};
};