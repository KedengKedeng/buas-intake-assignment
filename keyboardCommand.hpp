#pragma once
#include "command.hpp"
#include "keyboardSignals.hpp"

class EscapeCommand : public Command {
public:
	EscapeCommand() {}
	void execute() override { escapePressed.emit(); }
};