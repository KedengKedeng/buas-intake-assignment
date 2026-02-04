#include "countingStorage.hpp"

void CountingStorage::add(const std::string& name) {
	count[name]++;
}

void CountingStorage::remove(const std::string& name) {
	if (!count.count(name) || !count[name]) return;
	count[name]--;
}

int CountingStorage::get(const std::string& name) {
	if (!count.count(name)) return 0;
	return count[name];
}