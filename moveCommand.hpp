#pragma once
#include "command.hpp"
#include "playerSignals.hpp"
#include <cstdio>

//TODO: Dont make player velocity hardcoded?

class MoveCommand : public Command {
public:
	MoveCommand(int x, int y): x_(x), y_(y) {};
	void fire() override { WalkSignal::emit(x_, y_); }
private:
	int x_;
	int y_;
};