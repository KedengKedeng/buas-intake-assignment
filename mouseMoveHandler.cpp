#include "mouseMoveHandler.hpp"
#include "mouseSignals.hpp"

MouseMoveHandler::MouseMoveHandler() {
	subscribe();
}

MouseMoveHandler::~MouseMoveHandler() {
	unsubscribe();
}

void MouseMoveHandler::setOnMouseMove(std::function<void(Tmpl8::vec2&)> handler) {
	unsubscribe();
	onMouseMoveHandler_ = handler;
	subscribe();
}

void MouseMoveHandler::setOnMouseDrag(std::function<void(Tmpl8::vec2&)> handler) {
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
		if (onMouseMoveHandler_ != nullptr) onMouseMoveHandler_(pos);
		if (onMouseDragHandler_ != nullptr && mouseDown == true) onMouseDragHandler_(pos);
	});
}

void MouseMoveHandler::unsubscribe() {
	mouseDown = false;

	onMouseDownUnsub();
	onMouseUpUnsub();
	onMouseMoveUnsub();
}
