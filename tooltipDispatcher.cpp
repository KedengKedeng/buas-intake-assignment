#include "tooltipDispatcher.hpp"
#include "uiSignals.hpp"

void TooltipDispatcher::subscribe() {
	unsub = showTooltip.subscribe([this](std::shared_ptr<Tooltip> tooltip) {
		tooltips_[tooltip->getId()] = tooltip;
	});

	unsub2 = removeTooltip.subscribe([this](int64_t id) {
		tooltips_.erase(id);
	});
}

void TooltipDispatcher::unsubscribe() {
	unsub();
	unsub2();
}

void TooltipDispatcher::draw(Tmpl8::Surface* surface, vec2<float>& offset) {
	for (auto& tooltip : tooltips_) tooltip.second->draw(surface, offset);
}