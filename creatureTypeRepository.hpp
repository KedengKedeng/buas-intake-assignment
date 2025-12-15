#pragma once
#include <map>
#include <string>
#include <memory>
#include "creatureType.hpp"

class CreatureTypeRepository {
public:
	void insert(std::shared_ptr<CreatureType> creatureType) { registry_.insert({ creatureType->name, creatureType }); }
	std::shared_ptr<CreatureType> get(std::string& name) { return registry_[name]; }
private:
	std::map<std::string, std::shared_ptr<CreatureType>> registry_ = {};
};

extern CreatureTypeRepository creatureTypeRepository;
