#include "screen.hpp"

void Screen::process() {
	while (!queue.empty()) {
		auto func = queue.top();
		func();
		queue.pop();
	}
}