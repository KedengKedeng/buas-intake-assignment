#include "inventory.hpp"

void Inventory::addItem(std::string& itemName) {
	if (!itemCount.count(itemName)) itemCount[itemName] = 0;
	itemCount[itemName]++;
}

void Inventory::removeItem(std::string& itemName) {
	if (!itemCount.count(itemName)) return;
	itemCount[itemName]--;
	if (!itemCount[itemName]) itemCount.erase(itemName);
}