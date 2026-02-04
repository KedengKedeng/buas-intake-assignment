#pragma once
#include "item.hpp"
#include <vector>

class Cauldron {
public:
	Cauldron() {};

	void insertItem(std::shared_ptr<Item> item);
	size_t getItemCount() { return items_.size(); }

	void stir(float delta);
	void addTemp(float delta);
	float getTemp();

	void reset();
	std::vector<std::shared_ptr<Item>>& getItems();
private:
	float amountToStir = 0;
	float neededTemp = 0;
	float temp = 0;
	std::vector<std::shared_ptr<Item>> items_ = {};
};