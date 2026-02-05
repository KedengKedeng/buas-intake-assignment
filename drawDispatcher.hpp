#pragma once
#include "subscriptionManager.hpp"
#include "surface.h"
#include "vec2.hpp"
#include <unordered_map>
#include <functional>

class DrawDispatcher : public SubscriptionManager {
public:
	void subscribe() override;

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const;
private:
	std::unordered_map<int64_t, std::function<void(Tmpl8::Surface*, vec2<float>)>> toDraw = {};
};