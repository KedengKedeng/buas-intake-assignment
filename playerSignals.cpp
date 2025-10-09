#include "playerSignals.hpp"

void WalkSignal::emit(Vector2 delta){
	for (auto& subscriber : subscribers)
		subscriber(delta);
}

std::vector<std::function<void(Vector2)>> WalkSignal::subscribers;