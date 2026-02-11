#pragma once
#include "command.hpp"
#include "interactionSignal.hpp"

class InteractionCommand : public Command {
public:
	InteractionCommand() {}
	void execute() override { interactionSignal.emit(); }
};