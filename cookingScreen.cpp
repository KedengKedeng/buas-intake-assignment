#include "cookingScreen.hpp"
#include "wall.hpp"
#include "sprite.hpp"
#include "spoon.hpp"
#include "screenSignals.hpp"
#include "keyboardSignals.hpp"
#include "objectSignals.hpp"
#include "invisibleBarrier.hpp"
#include "random.hpp"
#include "objectRepository.hpp"

CookingScreen::CookingScreen(Tmpl8::Surface* surface) : Screen(surface), cauldron_(std::dynamic_pointer_cast<Cauldron>(objectRepository.get(std::string("cauldron")))) {
	cauldron_.setPos(Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight()) - cauldron_.getPos());
	auto cauldronSize = cauldron_.getBounds().getSize();
	// cauldron collision walls
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron_.getPos() + Tmpl8::vec2(80), Tmpl8::vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron_.getPos() + Tmpl8::vec2(cauldronSize.x - 100, 80.0f), Tmpl8::vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron_.getPos() + Tmpl8::vec2(80.0f, cauldronSize.y - 100), Tmpl8::vec2(cauldronSize.x - 140, 1.0f)));

	// screen edge collision walls
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(0, 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(surface->GetWidth(), 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(0, surface->GetHeight()), Tmpl8::vec2(surface->GetWidth(), 1)));

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

	requestMoveUnsub = requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Object& object) {
		Tmpl8::vec2 collides = objectsCollideWithBounds(object, velocity);

		Tmpl8::vec2 newPos = oldPos + newPos;

		if (oldPos != newPos) 
			object.setPos(oldPos + collides);
		
	});
}

void CookingScreen::unsubscribe() {
	Screen::unsubscribe();

	escapePressedUnsub();
	requestMoveUnsub();
}