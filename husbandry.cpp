#include "husbandry.hpp"

void Husbandry::addCreature(std::string& creatureName) {
	if (!creatures_.count(creatureName)) creatures_[creatureName] = 0;
	creatures_[creatureName]++;
}

void Husbandry::removeCreature(std::string& creatureName) {
	if (!creatures_.count(creatureName)) return;
	creatures_[creatureName]--;
	if (!creatures_[creatureName]) creatures_.erase(creatureName);
}