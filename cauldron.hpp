#pragma once
#include "item.hpp"
#include "object.hpp"
#include <vector>

class Cauldron : public Object {
public:
	Cauldron(): Object(0, vec2<float>(0.0f), vec2<float>(0.0f)) {};

	void insertItem(std::shared_ptr<Item> item);
	size_t getItemCount() { return items_.size(); }

	void stir(float delta);
	void addTemp(float delta);
	float getTemp();

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override {};
private:
	float amountToStir = 0;
	float neededTemp = 0;
	float temp = 0;
	std::vector<std::shared_ptr<Item>> items_ = {};
};