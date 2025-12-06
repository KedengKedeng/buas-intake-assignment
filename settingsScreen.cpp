#include "settingsScreen.hpp"
#include "container.hpp"
#include "button.hpp"
#include "screenSignals.hpp"
#include "keyboardSignals.hpp"

SettingsScreen::SettingsScreen(Tmpl8::Surface* surface) : Screen(surface) {
	auto container = std::make_unique<Container>(
		0,
		Tmpl8::vec2(surface->GetWidth() / 2 - 20, surface->GetHeight() / 2 - 30),
		Tmpl8::vec2(50),
		Justification::VERTICAL
	);

	container->insertObject(std::make_unique<Button>(
		0,
		[]() {},
		std::string("test button"),
		Tmpl8::vec2(0),
		Tmpl8::vec2(20)
	));

	insertObject(std::move(container));
	insertObject(std::make_unique<Button>(
		1,
		[]() {closeScreen.emit(); },
		std::string("exit"),
		Tmpl8::vec2(surface->GetWidth() / 2 + 30, surface->GetHeight() / 2 - 50),
		Tmpl8::vec2(20, 10)
	));
}

void SettingsScreen::draw(Tmpl8::Surface* surface) {
	int left = surface->GetWidth() / 2 - 50;
	int top = surface->GetHeight() / 2 - 50;
	int right = left + 100;
	int bottom = top + 100;
	surface->Bar(left, top, right, bottom, 0xffffff);

	Screen::draw(surface);
}

void SettingsScreen::subscribe() {
	Screen::subscribe();

	escapePressedUnsub = escapePressed.subscribe([]() {
		closeScreen.emit();
	});
}

void SettingsScreen::unsubscribe() {
	Screen::unsubscribe();

	escapePressedUnsub();
}