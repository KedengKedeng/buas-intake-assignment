#pragma once
#include "command.hpp"
#include "mouseSignals.hpp"

class MouseReleasedCommand : public Command {
public:
	void fire() override { mouseReleased.emit(); }
};