#pragma once
#include "command.hpp"
#include "playerSignals.hpp"
#include "vec2.hpp"

class MoveCommand : public Command {
public:
	MoveCommand(vec2<int8_t>& delta): delta_(delta) {};
	void execute() override { walkSignal.emit(delta_); }
	void undo() override { walkSignal.emit(-delta_); }
private:
	vec2<int8_t> delta_;
};