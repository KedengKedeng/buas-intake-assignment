#pragma once
#include "tooltip.hpp"
#include <map>
#include <memory>

class TooltipDispatcher {
public:
	void subscribe();
	void unsubscribe();

	void draw(Tmpl8::Surface* surface, vec2<float>& offset);
private:
	std::function<void()> unsub = []() {};
	std::function<void()> unsub2 = []() {};
	std::map<int64_t, std::shared_ptr<Tooltip>> tooltips_ = {};
};