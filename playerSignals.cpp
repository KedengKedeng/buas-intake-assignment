#include "playerSignals.hpp"

void WalkSignal::emit(int x, int y){
	for (auto& subscriber : subscribers)
		subscriber(x, y);
}

std::vector<std::function<void(int, int)>> WalkSignal::subscribers;