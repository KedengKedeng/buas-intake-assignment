#include "playerSignals.hpp"

void WalkLeftSignal::emit(int x){
	for (auto& subscriber : subscribers)
		subscriber(x);
}

std::vector<std::function<void(int)>> WalkLeftSignal::subscribers;