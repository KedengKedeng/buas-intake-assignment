#pragma once
#include "item.hpp"
#include <vector>

class Cauldron {
public:
	Cauldron() {};

	void insertItem(std::shared_ptr<Item> item);
	size_t getItemCount() const { return items_.size(); }

	void stir(float delta);
	void addTemp(float delta);
	float getTemp() const;

	void reset();
	const std::vector<std::shared_ptr<Item>>& getItems() const;
private:
	float amountToStir = 0;
	float neededTemp = 0;
	float temp = 0;
	std::vector<std::shared_ptr<Item>> items_ = {};
};