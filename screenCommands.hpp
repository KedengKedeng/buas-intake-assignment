#pragma once
#include "command.hpp"
#include "screenSignals.hpp"

class ChangeScreenCommand : public Command {
public:
	ChangeScreenCommand(Screens screen) : screen_(screen) {}
	void execute() override { changeScreen.emit(screen_); }
private:
	Screens screen_;
};

class StackScreenCommand : public Command {
public:
	StackScreenCommand(Screens screen) : screen_(screen) {}
	void execute() override { stackScreen.emit(screen_); }
private:
	Screens screen_;
};

class CloseScreenCommand : public Command {
public:
	CloseScreenCommand() {}
	void execute() override { closeScreen.emit(); }
};