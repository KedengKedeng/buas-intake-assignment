#pragma once
#include "creature.hpp"
#include "plot.hpp"

class Husbandry {
public:
	Husbandry() {};

	void addCreature(std::string& creatureName);
	void removeCreature(std::string& creatureName);

	void addPlot(std::shared_ptr<Plot> plot) { plots_.push_back(plot); }
	std::vector<std::shared_ptr<Plot>>& getPlots() { return plots_; }

	std::map<std::string, int>::iterator begin() { return creatures_.begin(); }
	std::map<std::string, int>::iterator end() { return creatures_.end(); }
private:
	int plotPrice = 0;
	std::vector<std::shared_ptr<Plot>> plots_;
	std::map<std::string, int> creatures_;
};