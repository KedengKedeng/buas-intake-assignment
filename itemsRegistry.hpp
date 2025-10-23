#pragma once
#include <map>
#include <string>
#include <memory>
#include "item.hpp"

class ItemRegistry {
public:
	void insert(std::shared_ptr<Item> item) { registry_.insert({item->name, item}); }
	std::shared_ptr<Item> get(std::string name) { return registry_[name]; }
private:
	std::map<std::string, std::shared_ptr<Item>> registry_ = {};
};

extern ItemRegistry itemRegistry;
