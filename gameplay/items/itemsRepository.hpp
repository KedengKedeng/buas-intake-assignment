#pragma once
#include <map>
#include <memory>
#include "item.hpp"

class ItemRepository {
public:
	ItemRepository();

	void insert(std::shared_ptr<Item> item) { registry_.insert({ item->id, item }); }
	std::shared_ptr<Item> get(Items item) { return registry_.at(item); }
private:
	std::map<Items, std::shared_ptr<Item>> registry_ = {};
};

static ItemRepository& itemRepository() {
	static ItemRepository repo;
	return repo;
}
