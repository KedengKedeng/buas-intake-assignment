#pragma once
#include <set>
#include "items.hpp"

class ItemLog {
public:
	void logItem(Items item);
	bool checkLog(Items item) const;
	Items getRandomLogged() const;
private:
	std::set<Items> loggedItems_ = {};
};