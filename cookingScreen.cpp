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
#include "blower.hpp"
#include "screenCommands.hpp"

CookingScreen::CookingScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<ChangeScreenCommand>(Screens::Play); });

	std::unique_ptr<CookingCauldron> cauldron = std::make_unique<CookingCauldron>(getRandomNum(), std::dynamic_pointer_cast<Cauldron>(objectRepository.get("cauldron")));

	// get a reference of the cauldron for operations on it specifically later
	cauldronId = cauldron->getId();

	cauldron->setPos(Tmpl8::vec2(surface->GetWidth() / 2 - 100, surface->GetHeight()) - cauldron->getPos());
	auto cauldronSize = cauldron->getBounds().getSize();

	// cauldron collision walls
	// the collision system doesnt allow for unique shapes past filled squares right now.
	// so we have to instantiate each side like this outside of the object.
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + Tmpl8::vec2(80), Tmpl8::vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + Tmpl8::vec2(cauldronSize.x - 100, 80.0f), Tmpl8::vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + Tmpl8::vec2(80.0f, cauldronSize.y - 100), Tmpl8::vec2(cauldronSize.x - 140, 1.0f)));

	// screen edge collision walls
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(0, 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(surface->GetWidth(), 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(0, surface->GetHeight()), Tmpl8::vec2(surface->GetWidth(), 1)));

	// insert main interactable objects
	insertObject(std::make_unique<Spoon>(0, cauldron->getPos() + Tmpl8::vec2(cauldronSize.x, 0.0f) / 2));
	insertObject(std::make_unique<Blower>(1, cauldron->getPos() + Tmpl8::vec2(500, 180)));
	insertObject(std::move(cauldron));
}

CookingScreen::~CookingScreen() {
	unsubscribe();
}

void CookingScreen::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	auto cauldron = dynamic_cast<CookingCauldron*>(objects_[cauldronId].get());
	cauldron->drawBack(surface);

	Screen::draw(surface, offset);

	cauldron->drawFront(surface);
}

void CookingScreen::subscribe() {
	Screen::subscribe();

	unsubscribers.push_back(cauldronInteracted.subscribe([this]() {
		trackSpoonMovement = true;
	}));

	unsubscribers.push_back(cauldronInteractionEnded.subscribe([this]() {
		trackSpoonMovement = false;
	}));

	unsubscribers.push_back(blowerInteracted.subscribe([this]() {
		trackBlowerMovement = true;
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {onBlow(delta); });
	}));

	unsubscribers.push_back(blowerInteractionEnded.subscribe([this]() {
		trackBlowerMovement = false;
		blowedSignalUnsub();
	}));

	unsubscribers.push_back(requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Object& object) {
		Tmpl8::vec2 collides = objectsCollideWithBounds(object, velocity);

		Tmpl8::vec2 newPos = oldPos + newPos;

		if (oldPos != newPos) 
			object.setPos(oldPos + collides);

		interactionCheck(object.getAbsoluteInteractionBounds());

		auto cauldron = dynamic_cast<CookingCauldron*>(objects_[cauldronId].get());
		if (trackSpoonMovement && oldPos != newPos) 
			cauldron->stir(std::abs(collides.x));
	}));

	// Only subscribe if the blower is being interacted with
	if (trackBlowerMovement)
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {onBlow(delta); });
}

void CookingScreen::unsubscribe() {
	Screen::unsubscribe();

	blowedSignalUnsub();
}