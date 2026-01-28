#pragma once
#include "tooltip.hpp"
#include "subscriptionManager.hpp"
#include <map>
#include <memory>

class TooltipDispatcher : public SubscriptionManager {
public:
	void subscribe() override;

	void draw(Tmpl8::Surface* surface, vec2<float>& offset);
private:
	std::map<int64_t, std::shared_ptr<Tooltip>> tooltips_ = {};
};