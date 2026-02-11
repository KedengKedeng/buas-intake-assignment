#include "plot.hpp"

std::optional<std::shared_ptr<Item>> Plot::progressProduction(float timePassed) {
	if (amount_ == 0) return std::nullopt;

	productionTimePassed += timePassed;
	// produce faster with more animals
	float neededProductionTime = (amount_ == 0) ? std::numeric_limits<float>::infinity() : creatureType_->timeToProduce / amount_;
	if (productionTimePassed >= neededProductionTime) {
		productionTimePassed = 0;
		return creatureType_->producedItem;
	}

	return std::nullopt;
}