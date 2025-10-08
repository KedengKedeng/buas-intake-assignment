#include "keyboardInput.hpp"
#include "moveLeftCommand.hpp"

enum KeyCodes
{
	LEFT = 4,
	UP = 26,
	DOWN = 22,
	RIGHT = 7
};

std::unique_ptr<Command> KeyboardInput::keyDown(int keyCode) {
	switch (keyCode)
	{
	case KeyCodes::LEFT:
		return std::make_unique<StartMoveLeftCommand>();
		break;
	default:
		return std::make_unique<Command>();
		break;
	}
}

std::unique_ptr<Command> KeyboardInput::keyUp(int keyCode) {
	switch (keyCode)
	{
	case KeyCodes::LEFT:
		return std::make_unique<EndMoveLeftCommand>();
		break;
	default:
		return std::make_unique<Command>();
		break;
	}
}