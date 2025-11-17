#include "startScreen.hpp"
#include "button.hpp"
#include "screenSignals.hpp"

StartScreen::StartScreen(Tmpl8::Surface* surface) : Screen(surface) {
	auto container = std::make_unique<Container>(
		getRandomNum(),
		Tmpl8::vec2(surface->GetWidth() / 2 - 30, surface->GetHeight() / 2 - 42),
		Tmpl8::vec2(60, 75),
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
		[]() { stackScreen.emit(2); },
		std::string{ "Settings" },
		Tmpl8::vec2(0),
		Tmpl8::vec2(60, 20),
		2
	));

	container->insertObject(std::make_unique<Button>(
		2,
		[]() { exit(0); },
		std::string{ "exit" },
		Tmpl8::vec2(0),
		Tmpl8::vec2(60, 20),
		2
	));

	insertObject(std::move(container));
};