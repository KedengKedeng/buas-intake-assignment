#include "startScreen.hpp"
#include "button.hpp"
#include "screenSignals.hpp"
#include "screenCommands.hpp"

StartScreen::StartScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler(std::string("escape"), []() {return std::make_unique<StackScreenCommand>(Screens::SettingsMenu); });

	Tmpl8::vec2 containerSize = {70, 75};
	Tmpl8::vec2 buttonSize = { 70, 20 };

	auto container = std::make_unique<Container>(
		getRandomNum(),
		(Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) - containerSize) / 2,
		containerSize,
		Justification::VERTICAL
	);

	container->insertObject(std::make_unique<Button>(
		0,
		[]() { changeScreen.emit(Screens::Play); },
		std::string{ "Start game" },
		Tmpl8::vec2(0),
		buttonSize,
		2
	));

	container->insertObject(std::make_unique<Button>(
		1,
		[]() { stackScreen.emit(Screens::SettingsMenu); },
		std::string{ "Settings" },
		Tmpl8::vec2(0),
		buttonSize,
		2
	));

	container->insertObject(std::make_unique<Button>(
		2,
		[]() { exit(0); },
		std::string{ "exit" },
		Tmpl8::vec2(0),
		buttonSize,
		2
	));

	insertObject(std::move(container));
};