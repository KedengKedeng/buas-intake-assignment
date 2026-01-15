#pragma once
#include "countingStorage.hpp"

class Inventory : public CountingStorage {
public:
	int getItemTypeCount() { return static_cast<int>(count.size()); }
};