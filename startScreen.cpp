#include "startScreen.hpp"

StartScreen::StartScreen(Tmpl8::Surface* surface) : Screen(surface) {
	buttons_.push_back(std::make_unique<Button>(
		0,
		[]() { changeScreen.emit(0); },
		std::string{ "Start game" },
		Tmpl8::vec2(surface_->GetWidth() / 2 - 30, surface_->GetHeight() / 2 - 10),
		Tmpl8::vec2(60, 20),
		2
	));
};

void StartScreen::draw() {
	for (auto& button : buttons_)
		button->draw(surface_);
}

void StartScreen::process() {
	surface_->Clear(255);

	draw();
}