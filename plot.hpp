#pragma once
#include "creature.hpp"

class Plot {
public:
	Plot() {};
	Plot(std::shared_ptr<CreatureType> type) : creatureType_(type) {}

	std::shared_ptr<CreatureType> getType() { return creatureType_; }
	void setCreatureType(std::shared_ptr<CreatureType> creatureType) { creatureType_ = creatureType; }
	void addCreature() { amount_++; }
	int getAmount() { return amount_; }

	void setBought(bool bought) { bought_ = bought; }
	bool getBought() { return bought_; }

	void setLevel(int level) { level_ = level; }
	void levelUp() { level_++; }
	int getLevel() { return level_; }
private:
	bool bought_ = false;
	std::shared_ptr<CreatureType> creatureType_;
	int amount_ = 0;
	int level_ = 0;
};