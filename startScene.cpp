#include "startScene.hpp"
#include "button.hpp"
#include "sceneSignals.hpp"
#include "sceneCommands.hpp"
#include "random.hpp"

StartScene::StartScene(Tmpl8::Surface& surface) : Scene(surface) {
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<StackSceneCommand>(Scenes::SettingsMenu); });

	vec2<float> containerSize(70, 75);
	vec2<float> buttonSize(70, 20);

	auto container = std::make_shared<ObjectContainer>(
		getRandomNum(),
		(vec2<float>(surface.GetWidth(), surface.GetHeight()) - containerSize) / 2,
		containerSize,
		Justification::VERTICAL,
		vec2(0.0f, 10.0f)
	);

	container->insertObject(std::make_shared<Button>(
		0,
		[]() { changeScene.emit(Scenes::Play); },
		std::string{ "Start game" },
		vec2(0.0f),
		buttonSize,
		2
	));

	container->insertObject(std::make_shared<Button>(
		1,
		[]() { stackScene.emit(Scenes::SettingsMenu); },
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