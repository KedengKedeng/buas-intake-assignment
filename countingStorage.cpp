#include "countingStorage.hpp"

void CountingStorage::add(std::string& name) {
	if (!count.count(name)) count[name] = 0;
	count[name]++;
}

void CountingStorage::remove(std::string& name) {
	if (!count.count(name)) return;
	count[name]--;
	if (!count[name]) count.erase(name);
}