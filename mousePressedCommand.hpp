#pragma once
#include "command.hpp"
#include "mouseSignals.hpp"

class MousePressedCommand : public Command {
public:
	MousePressedCommand(int x, int y) : x_(x), y_(y) {}
	void execute() override { mousePressed.emit(x_, y_); }
private:
	int x_;
	int y_;
};