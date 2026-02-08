#pragma once
#include "countingStorage.hpp"
#include "itemsRepository.hpp"

class Inventory : public CountingStorage<Items> {
public:
	int getItemTypeCount() const { return static_cast<int>(count.size()); }
};