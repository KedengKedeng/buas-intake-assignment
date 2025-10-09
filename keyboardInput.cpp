#include "keyboardInput.hpp"
#include "moveCommand.hpp"

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
		return std::make_unique<MoveCommand>(-10, 0);
		break;
	case KeyCodes::UP:
		return std::make_unique<MoveCommand>(0, -10);
		break;
	case KeyCodes::DOWN:
		return std::make_unique<MoveCommand>(0, 10);
		break;
	case KeyCodes::RIGHT:
		return std::make_unique<MoveCommand>(10, 0);
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
		return std::make_unique<MoveCommand>(10, 0);
		break;
	case KeyCodes::UP:
		return std::make_unique<MoveCommand>(0, 10);
		break;
	case KeyCodes::DOWN:
		return std::make_unique<MoveCommand>(0, -10);
		break;
	case KeyCodes::RIGHT:
		return std::make_unique<MoveCommand>(-10, 0);
		break;
	default:
		return std::make_unique<Command>();
		break;
	}
}