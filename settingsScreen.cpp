#include "settingsScreen.hpp"
#include "container.hpp"
#include "button.hpp"
#include "screenSignals.hpp"
#include "screenCommands.hpp"
#include "modal.hpp"

SettingsScreen::SettingsScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<CloseScreenCommand>(); });

	vec2<float> modalSize(100, 100);
	auto container = std::make_shared<Modal>(
		0,
		vec2<float>(surface->GetWidth(), surface->GetHeight()) / 2 - modalSize / 2,
		modalSize,
		[]() {closeScreen.emit(); },
		Justification::VERTICAL,
		vec2(10.0f)
	);

	container->insertObject(std::make_shared<Button>(
		0,
		[]() {},
		"test button",
		vec2(0.0f),
		vec2(20.0f)
	));

	insertObject(container);
}

void SettingsScreen::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	Screen::draw(surface, offset);
}