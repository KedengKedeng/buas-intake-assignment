#pragma once
#include "surface.h"
#include "object.hpp"
#include "vec2.hpp"
#include "text.hpp"
#include "subscriptionManager.hpp"
#include "clickable.hpp"
#include <functional>

class Button : public Object, public SubscriptionManager, public Clickable {
public:
	Button(
		int64_t id,
		std::function<void()> handler,
		const std::string& text,
		vec2<float>& pos = vec2<float>(0.0f),
		vec2<float>& size = vec2<float>(0.0f),
		int borderWidth = 1,
		Tmpl8::Pixel color = 0xffffffff,
		Tmpl8::Pixel borderColor = 0xff000000
	);

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override {}

	void subscribe() override;
private:
	int borderWidth_;
	Tmpl8::Pixel color_;
	Tmpl8::Pixel borderColor_;
	Text text_;
};