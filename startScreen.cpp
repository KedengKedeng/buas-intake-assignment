#include "startScreen.hpp"
#include "button.hpp"
#include "screenSignals.hpp"

StartScreen::StartScreen(Tmpl8::Surface* surface) : Screen(surface) {
	auto container = std::make_unique<Container>(
		getRandomNum(),
		Tmpl8::vec2(surface_->GetWidth() / 2 - 30, surface_->GetHeight() / 2 - 25),
		Tmpl8::vec2(60, 50),
		Justification::VERTICAL
	);

	container->insertObject(std::make_unique<Button>(
		0,
		[]() { changeScreen.emit(1); },
		std::string{ "Start game" },
		Tmpl8::vec2(0),
		Tmpl8::vec2(60, 20),
		2
	));

	container->insertObject(std::make_unique<Button>(
		1,
		[]() { exit(0); },
		std::string{ "exit" },
		Tmpl8::vec2(0),
		Tmpl8::vec2(60, 20),
		2
	));

	insertObject(std::move(container));
};

void StartScreen::process() {
	surface_->Clear(255);

	Screen::process();

	draw(surface_);
}