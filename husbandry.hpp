#pragma once
#include "creature.hpp"
#include "plot.hpp"
#include "countingStorage.hpp"

class Husbandry : public CountingStorage {
public:
	Husbandry() {};

	void addPlot(std::shared_ptr<Plot> plot) { plots_.push_back(plot); }
	std::vector<std::shared_ptr<Plot>>& getPlots() { return plots_; }
private:
	int plotPrice = 0;
	std::vector<std::shared_ptr<Plot>> plots_;
};