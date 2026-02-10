#include "itemLog.hpp"
#include "random.hpp"
#include <iterator>

void ItemLog::logItem(Items item) {
	loggedItems_.insert(item);
}

bool ItemLog::checkLog(Items item) const {
	return loggedItems_.find(item) != loggedItems_.end();
}

Items ItemLog::getRandomLogged() const {
	return *std::next(loggedItems_.begin(), getRandomNum() % loggedItems_.size());
}