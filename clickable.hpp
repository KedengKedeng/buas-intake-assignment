#pragma once
#include "mouseHandler.hpp"

class Clickable {
public:
	Clickable(std::function<void()> handler);
protected:
	MouseHandler mouseHandler_;
private:
	std::function<void()> handler_;
};