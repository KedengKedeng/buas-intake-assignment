#pragma once
#include "command.hpp"
#include <memory>
#include <set>

class KeyboardInput {
public:
	std::unique_ptr<Command> keyDown(int keyCode);
	std::unique_ptr<Command> keyUp(int keyCode);
private:
	std::set<int> keysDown = {};
};