#pragma once
#include "mouseMoveHandler.hpp"

class Clickable {
public:
	Clickable(std::function<void()> handler);
protected:
	MouseMoveHandler mouseMoveHandler_;
private:
	std::function<void()> handler_;
};