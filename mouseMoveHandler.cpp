#include "mouseMoveHandler.hpp"
#include "mouseSignals.hpp"

MouseMoveHandler::MouseMoveHandler() {

}

MouseMoveHandler::~MouseMoveHandler() {
	unsubscribe();
}

void MouseMoveHandler::setOnMouseMove(std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> handler) {
	unsubscribe();
	onMouseMoveHandler_ = handler;
}

void MouseMoveHandler::setOnMouseDrag(std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> handler) {
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
	if (onMouseDragHandler_ != nullptr) {
		printf("bla\n");
		onMouseDownUnsub = onMouseDown.subscribe([this](Tmpl8::vec2& pos) {
			if (interactionCheck(pos)) mouseDown = true;
			if (onMouseDragStartHandler_ != nullptr) onMouseDragStartHandler_();
		});

		onMouseUpUnsub = onMouseUp.subscribe([this]() {
			if (mouseDown && onMouseDragEndHandler_ != nullptr) onMouseDragEndHandler_();
			mouseDown = false;
		});
	}

	onMouseMoveUnsub = mouseMoved.subscribe([this](Tmpl8::vec2& pos) {
		Tmpl8::vec2 delta = pos - oldPos;

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
