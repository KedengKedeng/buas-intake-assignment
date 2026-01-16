#include "modal.hpp"

vec2 BUTTON_SIZE(10.0f);

Modal::Modal(int64_t id, vec2<float>& pos, vec2<float>& size, std::function<void()> onExitHandler, Justification justification)
	: Container(id, pos, size, Justification::VERTICAL), 
	exitButton(0, onExitHandler, "X", vec2(pos.x + size.x - BUTTON_SIZE.x, pos.y), BUTTON_SIZE),
	innerContainer_(0, pos + BUTTON_SIZE, size - BUTTON_SIZE, justification){

}

void Modal::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Bar(
		pos_.x,
		pos_.y,
		pos_.x + size_.x,
		pos_.y + size_.y,
		0xffffff
	);

	exitButton.draw(surface, offset);
	innerContainer_.draw(surface, offset);
}

void Modal::subscribe() {
	Container::subscribe();

	exitButton.subscribe();
	innerContainer_.subscribe();
}

void Modal::unsubscribe() {
	Container::unsubscribe();

	exitButton.unsubscribe();
	innerContainer_.unsubscribe();
}