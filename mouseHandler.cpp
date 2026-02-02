#include "mouseHandler.hpp"
#include "mouseSignals.hpp"

MouseHandler::~MouseHandler() {
	unsubscribe();
}

void MouseHandler::setOnMouseMove(std::function<void(vec2<float>&, vec2<float>&)> handler) {
	unsubscribe();
	onMouseMoveHandler_ = handler;
}

void MouseHandler::setOnMouseDrag(std::function<void(vec2<float>&, vec2<float>&)> handler) {
	unsubscribe();
	onMouseDragHandler_ = handler;
}

void MouseHandler::setOnMouseDown(std::function<void()> handler) {
	onMouseDownHandler_ = handler;
}

void MouseHandler::setOnMouseUp(std::function<void()> handler) {
	onMouseUpHandler_ = handler;
}

void MouseHandler::subscribe() {
	addSubscription(onMouseDown.subscribe([this](vec2<float>& pos) {
		if (interactionCheck(pos)) mouseDown = true;
		if (onMouseDownHandler_ != nullptr) onMouseDownHandler_();
	}));

	addSubscription(onMouseUp.subscribe([this]() {
		if (mouseDown && onMouseUpHandler_ != nullptr) onMouseUpHandler_();
		mouseDown = false;
	}));

	addSubscription(mouseMoved.subscribe([this](vec2<float>& pos) {
		vec2<float> delta = pos - oldPos;

		if (onMouseMoveHandler_ != nullptr) onMouseMoveHandler_(pos, delta);
		if (onMouseDragHandler_ != nullptr && mouseDown == true) onMouseDragHandler_(pos, delta);

		oldPos = pos;
	}));
}

void MouseHandler::unsubscribe() {
	SubscriptionManager::unsubscribe();

	mouseDown = false;
}
