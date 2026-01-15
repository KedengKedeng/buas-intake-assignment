#pragma once
#include "command.hpp"
#include "vec2.hpp"
#include <memory>
#include <set>

class MouseInput {
public:
	std::unique_ptr<Command> mouseDown(int button);
	std::unique_ptr<Command> mouseUp(int button);
	std::unique_ptr<Command> setMousePos(vec2<float>& pos);
private:
	vec2<float> pos_;
	std::set<int> buttonsDown = {};
};