#include "mouseMoveHandler.hpp"
#include "mouseSignals.hpp"

MouseMoveHandler::MouseMoveHandler() {}

MouseMoveHandler::~MouseMoveHandler() {
	unsubscribe();
}

void MouseMoveHandler::setOnMouseMove(std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> handler) {
	unsubscribe();
	onMouseMoveHandler_ = handler;
	subscribe();
}

void MouseMoveHandler::setOnMouseDrag(std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> handler) {
	unsubscribe();
	onMouseDragHandler_ = handler;
	subscribe();
}

void MouseMoveHandler::subscribe() {
	if (onMouseDragHandler_ != nullptr) {
		onMouseDownUnsub = mousePressed.subscribe([this](Tmpl8::vec2& pos) {
			if (interactionCheck(pos)) mouseDown = true;
		});

		onMouseUpUnsub = mouseReleased.subscribe([this]() {
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
