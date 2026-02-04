#include "cauldron.hpp"
#include "recipeBook.hpp"

void Cauldron::insertItem(std::shared_ptr<Item> item) { 
	items_.push_back(item); 
	amountToStir += 1000;
}

void Cauldron::stir(float delta) {
	if (items_.size() == 0 || temp < 200) return;

	amountToStir -= delta;

	if (amountToStir <= 0) {
		auto output = recipeBook.lookup(items_);

		if (output == nullptr) {
			amountToStir += 1000 * items_.size();
			return;
		}

		amountToStir = 0;
		items_.clear();
		temp = 0;
		printf(output->name.c_str());
	}
}

void Cauldron::addTemp(float delta) {
	if (delta < 0) return;
	temp += delta;
}

float Cauldron::getTemp() {
	return temp;
}

void Cauldron::reset() {
	temp = 0;
	items_.clear();
	amountToStir = 0;
}

std::vector<std::shared_ptr<Item>>& Cauldron::getItems() {
	return items_;
}