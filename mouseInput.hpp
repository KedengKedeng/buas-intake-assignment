#pragma once
#include "command.hpp"
#include "template.h"
#include <memory>
#include <set>

class MouseInput {
public:
	std::unique_ptr<Command> mouseDown(int button);
	std::unique_ptr<Command> mouseUp(int button);
	std::unique_ptr<Command> setMousePos(Tmpl8::vec2& pos);
private:
	Tmpl8::vec2 pos_;
	std::set<int> buttonsDown = {};
};