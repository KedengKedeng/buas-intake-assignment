#include "startScreen.hpp"
#include "button.hpp"
#include "screenSignals.hpp"
#include "screenCommands.hpp"
#include "random.hpp"

StartScreen::StartScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<StackScreenCommand>(Screens::SettingsMenu); });

	vec2<float> containerSize(70, 75);
	vec2<float> buttonSize(70, 20);

	auto container = std::make_shared<Container>(
		getRandomNum(),
		(vec2<float>(surface->GetWidth(), surface->GetHeight()) - containerSize) / 2,
		containerSize,
		Justification::VERTICAL,
		vec2(0.0f, 10.0f)
	);

	container->insertObject(std::make_shared<Button>(
		0,
		[]() { changeScreen.emit(Screens::Play); },
		std::string{ "Start game" },
		vec2(0.0f),
		buttonSize,
		2
	));

	container->insertObject(std::make_shared<Button>(
		1,
		[]() { stackScreen.emit(Screens::SettingsMenu); },
		std::string{ "Settings" },
		vec2(0.0f),
		buttonSize,
		2
	));

	container->insertObject(std::make_shared<Button>(
		2,
		[]() { exit(0); },
		std::string{ "exit" },
		vec2(0.0f),
		buttonSize,
		2
	));

	insertObject(container);
};