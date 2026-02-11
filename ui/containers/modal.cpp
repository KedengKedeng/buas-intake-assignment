#include "modal.hpp"
#include "boundingBox.hpp"

vec2 BUTTON_SIZE(10.0f);

Modal::Modal(
	int64_t id, 
	vec2<float> pos, 
	vec2<float> size, 
	std::function<void()> onExitHandler, 
	Justification justification, 
	vec2<float> gap, 
	bool scrollable
) : 
	Object(id, pos, size), 
	Clickable(true),
	exitButton(0, onExitHandler, "X", vec2(pos.x + size.x - BUTTON_SIZE.x, pos.y), BUTTON_SIZE),
	innerContainer_(0, pos + BUTTON_SIZE, size - BUTTON_SIZE, justification, gap, scrollable)
{}

Modal::~Modal() {
	unsubscribe();
}

vec2<float> Modal::getPadding() const {
	return BUTTON_SIZE;
}

void Modal::onMouseDown(vec2<float> pos, vec2<float> screenPos) {
	innerContainer_.onMouseDown(pos, screenPos);
	if (BoundingBox(exitButton.getPos(), exitButton.getSize()).isInBounds(pos)) exitButton.onMouseDown(pos, screenPos);
};

void Modal::onMouseUp(vec2<float> pos, vec2<float> screenPos) {
	innerContainer_.onMouseUp(pos, screenPos);
};

void Modal::onMouseMove(vec2<float> pos, vec2<float> screenPos, vec2<float> delta) {
	innerContainer_.onMouseMove(pos, screenPos, delta);
};

void Modal::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	surface.Bar(vec2(0.0f), vec2<float>(surface.GetWidth(), surface.GetHeight()), 0x40000000);
	auto pos = getPos();
	surface.Bar(pos, pos + getSize(), 0xffffffff);

	exitButton.draw(surface, offset);
	innerContainer_.draw(surface, offset);
}

void Modal::process(float deltaTime) {
	exitButton.process(deltaTime);
	innerContainer_.process(deltaTime);
}

void Modal::subscribe() {
	SubscriptionManager::subscribe();

	innerContainer_.subscribe();
}

void Modal::unsubscribe() {
	SubscriptionManager::unsubscribe();

	innerContainer_.unsubscribe();
}