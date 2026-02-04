#include "drawDispatcher.hpp"
#include "uiSignals.hpp"

void DrawDispatcher::subscribe() {
	addSubscription(drawOnTop.subscribe([this](int64_t id, std::function<void(Tmpl8::Surface*, const vec2<float>&)> drawFunc) {
		toDraw[id] = drawFunc;
	}));

	addSubscription(removeDrawOnTop.subscribe([this](int64_t id) {
		toDraw.erase(id);
	}));
}

void DrawDispatcher::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	for (auto& [_, func] : toDraw) func(surface, offset);
}