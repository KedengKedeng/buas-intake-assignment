#pragma once
#include "item.hpp"
#include <map>

class Inventory {
public:
	void addItem(std::string& itemName);
	void removeItem(std::string& itemName);

	int getItemTypeCount() { return itemCount.size(); }

	std::map<std::string, int>::iterator begin() { return itemCount.begin(); }
	std::map<std::string, int>::iterator end() { return itemCount.end(); }
private:
	std::map<std::string, int> itemCount = {};
};