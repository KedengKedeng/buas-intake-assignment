#include "cookingScreen.hpp"
#include "wall.hpp"
#include "sprite.hpp"
#include "spoon.hpp"
#include "screenSignals.hpp"
#include "keyboardSignals.hpp"

CookingScreen::CookingScreen(Tmpl8::Surface* surface) : Screen(surface), cauldron_() {
	cauldron_.setPos(Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight()) - cauldron_.getPos());

	insertObject(std::make_unique<Spoon>(0, Tmpl8::vec2(10)));
}

CookingScreen::~CookingScreen() {
	unsubscribe();
}

void CookingScreen::draw(Tmpl8::Surface* surface) {
	cauldron_.drawBack(surface);

	Screen::draw(surface);

	cauldron_.drawFront(surface);
}

void CookingScreen::process() {
	Screen::process();
}

void CookingScreen::subscribe() {
	Screen::subscribe();

	escapePressedUnsub = escapePressed.subscribe([]() {
		changeScreen.emit(1);
	});
}

void CookingScreen::unsubscribe() {
	Screen::unsubscribe();

	escapePressedUnsub();
}