#pragma once
#include "command.hpp"
#include "playerSignals.hpp"
#include "vector2.hpp"

class MoveCommand : public Command {
public:
	MoveCommand(Vector2 delta): delta_(delta) {};
	void fire() override { walkSignal.emit(delta_); }
private:
	Vector2 delta_;
};