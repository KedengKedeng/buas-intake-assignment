#pragma once
#include "template.h"
#include "boundingBox.hpp"
#include <functional>

class MouseMoveHandler {
public:
	MouseMoveHandler();
	~MouseMoveHandler();

	void setOnMouseMove(std::function<void(Tmpl8::vec2&)> handler);
	void setOnMouseDrag(std::function<void(Tmpl8::vec2&)> handler);
	void setInteractionCheck(std::function<bool(Tmpl8::vec2&)> func) { interactionCheck = func; }

	void subscribe();
	void unsubscribe();
private:
	std::function<void(Tmpl8::vec2&)> onMouseMoveHandler_ = nullptr;
	std::function<void(Tmpl8::vec2&)> onMouseDragHandler_ = nullptr;
	std::function<bool(Tmpl8::vec2&)> interactionCheck = [](Tmpl8::vec2& _) {return false; };

	bool mouseDown = false;

	std::function<void()> onMouseMoveUnsub = []() {};
	std::function<void()> onMouseDownUnsub = []() {};
	std::function<void()> onMouseUpUnsub = []() {};
};