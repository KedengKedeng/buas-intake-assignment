#pragma once
#include "command.hpp"
#include <memory>
#include <set>

class MouseInput {
public:
	std::unique_ptr<Command> mouseDown(int button);
	std::unique_ptr<Command> mouseUp(int button);
	std::unique_ptr<Command> setMousePos(int x, int y);
private:
	int x_;
	int y_;
	std::set<int> buttonsDown = {};
};