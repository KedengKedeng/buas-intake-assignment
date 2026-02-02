#include "clickable.hpp"

Clickable::Clickable(std::function<void()> handler) :
	handler_(handler),
	mouseHandler_()
{
	mouseHandler_.setOnMouseUp(handler_);
}