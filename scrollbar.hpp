#pragma once
#include "object.hpp"
#include "mouseHandler.hpp"
#include "subscriptionManager.hpp"
#include <functional>

class Scrollbar : public Object, public SubscriptionManager {
public:
	Scrollbar(int64_t id, vec2<float>& pos, vec2<float>& size, vec2<float>& parentSize, std::function<void(vec2<float>)> onDrag);
	
	void setParentSize(vec2<float>& size);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;

	void subscribe() override;
	void unsubscribe() override;
private:
	float getThumbSize();

	vec2<float> parentSize_;

	float thumbPos_;
	float thumbSize_;

	MouseHandler mouseHandler_;
	std::function<void(vec2<float>)> onDrag_;
};