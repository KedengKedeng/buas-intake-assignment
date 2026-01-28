#pragma once
#include "vec2.hpp"
#include <functional>

class MouseMoveHandler {
public:
	MouseMoveHandler() {};
	~MouseMoveHandler();

	void setOnMouseMove(std::function<void(vec2<float>&, vec2<float>&)> handler);
	void setOnMouseDrag(std::function<void(vec2<float>&, vec2<float>&)> handler);
	void setOnMouseDragStart(std::function<void()> handler);
	void setOnMouseDragEnd(std::function<void()> handler);
	void setInteractionCheck(std::function<bool(vec2<float>&)> func) { interactionCheck = func; }

	void subscribe();
	void unsubscribe();
private:
	std::function<void(vec2<float>&, vec2<float>&)> onMouseMoveHandler_;
	std::function<void(vec2<float>&, vec2<float>&)> onMouseDragHandler_;
	std::function<void()> onMouseDragStartHandler_;
	std::function<void()> onMouseDragEndHandler_;
	std::function<bool(vec2<float>&)> interactionCheck = [](vec2<float>& _) {return false; };

	bool mouseDown = false;
	vec2<float> oldPos = vec2(0.0f);

	std::function<void()> onMouseMoveUnsub = []() {};
	std::function<void()> onMouseDownUnsub = []() {};
	std::function<void()> onMouseUpUnsub = []() {};
};