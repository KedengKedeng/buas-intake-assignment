#include "screen.hpp"

void Screen::process() {
	Container::process();

	for (; !queue.empty(); queue.pop()) {
		auto func = queue.front();
		func();
	}
}