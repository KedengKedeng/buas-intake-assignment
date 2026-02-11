#pragma once
#include <map>
#include <memory>
#include "creatureType.hpp"

class CreatureTypeRepository {
	using CreatureTypeMap = std::map<CreatureTypes, std::shared_ptr<CreatureType>>;
public:
	CreatureTypeRepository();

	void insert(std::shared_ptr<CreatureType> creatureType);
	std::shared_ptr<CreatureType> get(CreatureTypes type);

	CreatureTypeMap::iterator begin() { return registry_.begin(); }
	CreatureTypeMap::iterator end() { return registry_.end(); }
private:
	CreatureTypeMap registry_ = {};
};

static CreatureTypeRepository& creatureTypeRepository() {
	static CreatureTypeRepository repo;
	return repo;
}