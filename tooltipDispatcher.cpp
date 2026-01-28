#include "tooltipDispatcher.hpp"
#include "uiSignals.hpp"

void TooltipDispatcher::subscribe() {
	addSubscription(showTooltip.subscribe([this](std::shared_ptr<Tooltip> tooltip) {
		tooltips_[tooltip->getId()] = tooltip;
	}));

	addSubscription(removeTooltip.subscribe([this](int64_t id) {
		tooltips_.erase(id);
	}));
}

void TooltipDispatcher::draw(Tmpl8::Surface* surface, vec2<float>& offset) {
	for (auto& tooltip : tooltips_) tooltip.second->draw(surface, offset);
}