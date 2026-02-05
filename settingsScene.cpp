#include "settingsScene.hpp"
#include "button.hpp"
#include "sceneSignals.hpp"
#include "sceneCommands.hpp"
#include "modal.hpp"

SettingsScene::SettingsScene(Tmpl8::Surface* surface) : Scene(surface) {
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<CloseSceneCommand>(); });

	vec2<float> modalSize(100, 100);
	auto modal = std::make_shared<Modal>(
		0,
		vec2<float>(surface->GetWidth(), surface->GetHeight()) / 2 - modalSize / 2,
		modalSize,
		[]() {closeScene.emit(); },
		Justification::VERTICAL,
		vec2(10.0f)
	);

	modal->insertObject(std::make_shared<Button>(
		0,
		[]() {},
		"test button",
		vec2(0.0f),
		vec2(20.0f)
	));

	insertObject(modal);
}

void SettingsScene::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	Scene::draw(surface, offset);
}