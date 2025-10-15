#pragma once
#include "command.hpp"
#include "mouseSignals.hpp"

class MouseReleasedCommand : public Command {
public:
	void execute() override { mouseReleased.emit(); }
};