#pragma once
#include <map>
#include <string>

class CountingStorage {
public:
	void add(const std::string& itemName);
	void remove(const std::string& itemName);
	int get(const std::string& itemName);

	std::map<std::string, int>::iterator begin() { return count.begin(); }
	std::map<std::string, int>::iterator end() { return count.end(); }
protected:
	std::map<std::string, int> count = {};
};