#pragma once
#include "creatureType.hpp"
#include "item.hpp"
#include <memory>
#include <optional>

class Plot {
public:
	Plot() {};
	Plot(std::shared_ptr<CreatureType> type) : creatureType_(type) {}

	std::shared_ptr<CreatureType> getType() const { return creatureType_; }
	void setCreatureType(std::shared_ptr<CreatureType> creatureType) { creatureType_ = creatureType; }
	void addCreature() { amount_++; }
	int getAmount() const { return amount_; }

	std::optional<std::shared_ptr<Item>> progressProduction(float timePassed);
private:
	float productionTimePassed = 0;
	std::shared_ptr<CreatureType> creatureType_;
	int amount_ = 0;
};