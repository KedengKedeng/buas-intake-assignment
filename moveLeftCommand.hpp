#pragma once
#include "command.hpp"
#include "playerSignals.hpp"

//TODO: Dont make player velocity hardcoded?

class StartMoveLeftCommand : public Command {
public:
	void fire() override { WalkLeftSignal::emit(-10); }
};

class EndMoveLeftCommand : public Command {
public:
	void fire() override { WalkLeftSignal::emit(10); }
};