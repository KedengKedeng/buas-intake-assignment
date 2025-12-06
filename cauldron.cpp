#include "cauldron.hpp"

void Cauldron::insertItem(std::shared_ptr<Item> item) { 
	items_.push_back(item); 
	amountToStir += 1000;
}

void Cauldron::stir(float delta) {
	if (items_.size() == 0) return;
	printf("%.f\n", delta);

	amountToStir -= delta;

	if (amountToStir <= 0) {
		amountToStir = 0;
		printf("stirring complete \n");
		items_.clear();
	}
}