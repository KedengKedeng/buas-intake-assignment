#pragma once
#include "plot.hpp"
#include "countingStorage.hpp"

class Husbandry : public CountingStorage<CreatureTypes> {
public:
	Husbandry() : CountingStorage() {};

	void addPlot(std::shared_ptr<Plot> plot) { plots_.push_back(plot); }
	const std::vector<std::shared_ptr<Plot>>& getPlots() const { return plots_; }
private:
	int plotPrice = 0;
	std::vector<std::shared_ptr<Plot>> plots_;
};