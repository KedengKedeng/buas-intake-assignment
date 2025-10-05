#pragma once
#include "command.hpp"

class MoveLeftCommand : public Command {
public:
	void fire() override;
};