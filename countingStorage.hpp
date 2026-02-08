#pragma once
#include <map>

template<typename T>
class CountingStorage {
public:
	void CountingStorage::add(const T& name) {
		count[name]++;
	}

	void remove(const T& name) {
		if (!count.count(name) || !count[name]) return;
		count[name]--;
		if (!count[name]) count.erase(name);
	}

	int get(const T& name) const {
		if (!count.count(name)) return 0;
		return count.at(name);
	}

	std::map<T, int>::iterator begin() { return count.begin(); }
	std::map<T, int>::iterator end() { return count.end(); }
protected:
	std::map<T, int> count = {};
};