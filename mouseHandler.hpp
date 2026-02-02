#pragma once
#include "vec2.hpp"
#include "subscriptionManager.hpp"
#include <functional>

class MouseHandler : public SubscriptionManager {
public:
	MouseHandler() {};
	~MouseHandler();

	void setOnMouseMove(std::function<void(vec2<float>&, vec2<float>&)> handler);
	void setOnMouseDrag(std::function<void(vec2<float>&, vec2<float>&)> handler);
	void setOnMouseDown(std::function<void()> handler);
	void setOnMouseUp(std::function<void()> handler);
	void setInteractionCheck(std::function<bool(vec2<float>&)> func) { interactionCheck = func; }

	void subscribe() override;
	void unsubscribe() override;
private:
	std::function<void(vec2<float>&, vec2<float>&)> onMouseMoveHandler_;
	std::function<void(vec2<float>&, vec2<float>&)> onMouseDragHandler_;
	std::function<void()> onMouseDownHandler_;
	std::function<void()> onMouseUpHandler_;
	std::function<bool(vec2<float>&)> interactionCheck = [](vec2<float>& _) {return false; };

	bool mouseDown = false;
	vec2<float> oldPos = vec2(0.0f);
};