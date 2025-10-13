#include "mouseInput.hpp"

std::unique_ptr<Command> MouseInput::mouseDown(int button) {
	auto exists = buttonsDown.find(button);
	if (exists != buttonsDown.end())
		return std::make_unique<Command>();
	else
		buttonsDown.insert(button);

	switch (button)
	{
	default:
		return std::make_unique<Command>();
		break;
	}
}

std::unique_ptr<Command> MouseInput::mouseUp(int button) {
	buttonsDown.erase(button);

	switch (button)
	{
	default:
		return std::make_unique<Command>();
		break;
	}
}

std::unique_ptr<Command> MouseInput::setMousePos(int x, int y) {
	return std::make_unique<Command>();
}