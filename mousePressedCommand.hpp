#pragma once
#include "command.hpp"
#include "mouseSignals.hpp"
#include "template.h"

class MousePressedCommand : public Command {
public:
	MousePressedCommand(Tmpl8::vec2& pos) : pos_(pos) {}
	void execute() override { onMouseDown.emit(pos_); }
private:
	Tmpl8::vec2 pos_;
};