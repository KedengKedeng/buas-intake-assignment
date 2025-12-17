#include "modal.hpp"

Tmpl8::vec2 BUTTON_SIZE = {10, 10};

Modal::Modal(int64_t id, Tmpl8::vec2& pos, Tmpl8::vec2& size, std::function<void()> onExitHandler, Justification justification)
	: Container(id, pos, size, Justification::VERTICAL), 
	exitButton(0, onExitHandler, "X", Tmpl8::vec2(pos.x + size.x - BUTTON_SIZE.x, pos.y), BUTTON_SIZE),
	innerContainer_(0, pos + BUTTON_SIZE, size - BUTTON_SIZE, justification){

}

void Modal::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	auto size = boundingBox_.getSize();
	surface->Bar(pos_.x, pos_.y, pos_.x + size.x, pos_.y + size.y, 0xffffff);

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