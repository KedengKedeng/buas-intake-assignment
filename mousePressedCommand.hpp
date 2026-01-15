#pragma once
#include "command.hpp"
#include "mouseSignals.hpp"

class MousePressedCommand : public Command {
public:
	MousePressedCommand(vec2<float>& pos) : pos_(pos) {}
	void execute() override { onMouseDown.emit(pos_); }
private:
	vec2<float> pos_;
};