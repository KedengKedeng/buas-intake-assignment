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
	// If we dont do this commands will continuously get triggered
	// by holding down a key.
	auto exists = keysDown.find(keyCode);
	if (exists != keysDown.end())
		return std::make_unique<Command>();
	else
		keysDown.insert(keyCode);

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
	keysDown.erase(keyCode);

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