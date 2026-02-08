#include "cauldron.hpp"
#include "recipeBook.hpp"

void Cauldron::insertItem(std::shared_ptr<Item> item) { 
	items_.push_back(item); 
	amountToStir += 1000;
}

std::shared_ptr<Item> Cauldron::stir(float delta) {
	if (items_.size() == 0 || temp < 200) return nullptr;

	amountToStir -= delta;

	if (amountToStir > 0) return nullptr;

	auto output = recipeBook.lookup(items_);

	if (output == nullptr) {
		amountToStir += 1000 * items_.size();
		return nullptr;
	}

	amountToStir = 0;
	items_.clear();
	temp = 0;
	return output;
}

void Cauldron::addTemp(float delta) {
	if (delta < 0) return;
	temp += delta;
}

float Cauldron::getTemp() const {
	return temp;
}

void Cauldron::reset() {
	temp = 0;
	items_.clear();
	amountToStir = 0;
}

const std::vector<std::shared_ptr<Item>>& Cauldron::getItems() const {
	return items_;
}