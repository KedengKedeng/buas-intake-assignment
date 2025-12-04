#pragma once
#include "template.h"
#include "boundingBox.hpp"
#include <functional>

class MouseMoveHandler {
public:
	MouseMoveHandler();
	~MouseMoveHandler();

	void setOnMouseMove(std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> handler);
	void setOnMouseDrag(std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> handler);
	void setOnMouseDragStart(std::function<void()> handler);
	void setOnMouseDragEnd(std::function<void()> handler);
	void setInteractionCheck(std::function<bool(Tmpl8::vec2&)> func) { interactionCheck = func; }

	void subscribe();
	void unsubscribe();
private:
	std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> onMouseMoveHandler_;
	std::function<void(Tmpl8::vec2&, Tmpl8::vec2&)> onMouseDragHandler_;
	std::function<void()> onMouseDragStartHandler_;
	std::function<void()> onMouseDragEndHandler_;
	std::function<bool(Tmpl8::vec2&)> interactionCheck = [](Tmpl8::vec2& _) {return false; };

	bool mouseDown = false;
	Tmpl8::vec2 oldPos = Tmpl8::vec2(0);

	std::function<void()> onMouseMoveUnsub = []() {};
	std::function<void()> onMouseDownUnsub = []() {};
	std::function<void()> onMouseUpUnsub = []() {};
};