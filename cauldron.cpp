#include "cauldron.hpp"

void Cauldron::insertItem(std::shared_ptr<Item> item) { 
	items_.push_back(item); 
	amountToStir += 1000;
}

void Cauldron::stir(float delta) {
	if (items_.size() == 0) return;

	amountToStir -= delta;

	if (amountToStir <= 0) {
		amountToStir = 0;
		printf("stirring complete \n");
		items_.clear();
	}
}

void Cauldron::addTemp(float delta) {
	temp += delta;
}

float Cauldron::getTemp() {
	return temp;
}