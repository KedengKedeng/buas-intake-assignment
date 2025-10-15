#pragma once
#include "command.hpp"
#include "playerSignals.hpp"
#include "template.h"

class MoveCommand : public Command {
public:
	MoveCommand(Tmpl8::vec2 delta): delta_(delta) {};
	void execute() override { walkSignal.emit(delta_); }
private:
	Tmpl8::vec2 delta_;
};