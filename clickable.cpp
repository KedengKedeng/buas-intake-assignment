#include "clickable.hpp"

Clickable::Clickable(std::function<void()> handler) :
	handler_(handler),
	mouseMoveHandler_()
{
	mouseMoveHandler_.setOnMouseDragEnd(handler_);
}