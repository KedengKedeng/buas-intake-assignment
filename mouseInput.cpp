#include "mouseInput.hpp"
#include "mousePressedCommand.hpp"
#include "mouseReleasedCommand.hpp"

std::unique_ptr<Command> MouseInput::mouseDown(int button) {
	auto exists = buttonsDown.find(button);
	if (exists != buttonsDown.end())
		return std::make_unique<Command>();
	else
		buttonsDown.insert(button);

	switch (button)
	{
	case 1:
		return std::make_unique<MousePressedCommand>(pos_);
		break;
	default:
		return std::make_unique<Command>();
		break;
	}
}

std::unique_ptr<Command> MouseInput::mouseUp(int button) {
	buttonsDown.erase(button);

	switch (button)
	{
	case 1:
		return std::make_unique<MouseReleasedCommand>();
		break;
	default:
		return std::make_unique<Command>();
		break;
	}
}

std::unique_ptr<Command> MouseInput::setMousePos(vec2<float>& pos) {
	pos_ = pos;
	mouseMoved.emit(pos);
	return std::make_unique<Command>();
}