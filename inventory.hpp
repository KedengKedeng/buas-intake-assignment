#pragma once
#include "countingStorage.hpp"

class Inventory : public CountingStorage {
public:
	int getItemTypeCount() const { return static_cast<int>(count.size()); }
};