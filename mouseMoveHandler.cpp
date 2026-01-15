#include "mouseMoveHandler.hpp"
#include "mouseSignals.hpp"

MouseMoveHandler::MouseMoveHandler() {

}

MouseMoveHandler::~MouseMoveHandler() {
	unsubscribe();
}

void MouseMoveHandler::setOnMouseMove(std::function<void(vec2<float>&, vec2<float>&)> handler) {
	unsubscribe();
	onMouseMoveHandler_ = handler;
}

void MouseMoveHandler::setOnMouseDrag(std::function<void(vec2<float>&, vec2<float>&)> handler) {
	unsubscribe();
	onMouseDragHandler_ = handler;
}

void MouseMoveHandler::setOnMouseDragStart(std::function<void()> handler) {
	onMouseDragStartHandler_ = handler;
}

void MouseMoveHandler::setOnMouseDragEnd(std::function<void()> handler) {
	onMouseDragEndHandler_ = handler;
}


void MouseMoveHandler::subscribe() {
	// dont bother subscribing if no drag handler has been set
	if (onMouseDragHandler_ != nullptr) {;
		onMouseDownUnsub = onMouseDown.subscribe([this](vec2<float>& pos) {
			if (interactionCheck(pos)) mouseDown = true;
			if (onMouseDragStartHandler_ != nullptr) onMouseDragStartHandler_();
		});

		onMouseUpUnsub = onMouseUp.subscribe([this]() {
			if (mouseDown && onMouseDragEndHandler_ != nullptr) onMouseDragEndHandler_();
			mouseDown = false;
		});
	}

	onMouseMoveUnsub = mouseMoved.subscribe([this](vec2<float>& pos) {
		vec2<float> delta = pos - oldPos;

		if (onMouseMoveHandler_ != nullptr) onMouseMoveHandler_(pos, delta);
		if (onMouseDragHandler_ != nullptr && mouseDown == true) onMouseDragHandler_(pos, delta);

		oldPos = pos;
	});
}

void MouseMoveHandler::unsubscribe() {
	mouseDown = false;

	onMouseDownUnsub();
	onMouseUpUnsub();
	onMouseMoveUnsub();
}
