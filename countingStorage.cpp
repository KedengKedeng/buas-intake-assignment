#include "countingStorage.hpp"

void CountingStorage::add(const std::string& name) {
	count[name]++;
}

void CountingStorage::remove(std::string& name) {
	if (!count.count(name)) return;
	count[name]--;
	if (!count[name]) count.erase(name);
}