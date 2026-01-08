#include "settingsScreen.hpp"
#include "container.hpp"
#include "button.hpp"
#include "screenSignals.hpp"
#include "keyboardSignals.hpp"
#include "screenCommands.hpp"
#include "modal.hpp"

SettingsScreen::SettingsScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<CloseScreenCommand>(); });

	Tmpl8::vec2 modalSize = { 100, 100 };
	auto container = std::make_shared<Modal>(
		0,
		Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) / 2 - modalSize / 2,
		modalSize,
		[]() {closeScreen.emit(); },
		Justification::VERTICAL
	);

	container->insertObject(std::make_shared<Button>(
		0,
		[]() {},
		"test button",
		Tmpl8::vec2(0),
		Tmpl8::vec2(20)
	));

	insertObject(container);
}

void SettingsScreen::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	Screen::draw(surface, offset);
}