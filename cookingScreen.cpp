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

CookingScreen::CookingScreen(Tmpl8::Surface* surface) : Screen(surface) {
	std::unique_ptr<CookingCauldron> cauldron = std::make_unique<CookingCauldron>(getRandomNum(), std::dynamic_pointer_cast<Cauldron>(objectRepository.get(std::string("cauldron"))));

	cauldronId = cauldron->getId();

	cauldron->setPos(Tmpl8::vec2(surface->GetWidth() / 2 - 100, surface->GetHeight()) - cauldron->getPos());
	auto cauldronSize = cauldron->getBounds().getSize();

	// cauldron collision walls
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + Tmpl8::vec2(80), Tmpl8::vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + Tmpl8::vec2(cauldronSize.x - 100, 80.0f), Tmpl8::vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + Tmpl8::vec2(80.0f, cauldronSize.y - 100), Tmpl8::vec2(cauldronSize.x - 140, 1.0f)));

	// screen edge collision walls
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(0, 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(surface->GetWidth(), 0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<InvisibleBarrier>(getRandomNum(), Tmpl8::vec2(0, surface->GetHeight()), Tmpl8::vec2(surface->GetWidth(), 1)));

	insertObject(std::make_unique<Spoon>(0, cauldron->getPos() + Tmpl8::vec2(cauldronSize.x, 0.0f) / 2));
	insertObject(std::make_unique<Blower>(1, cauldron->getPos() + Tmpl8::vec2(500, 180)));
	insertObject(std::move(cauldron));
}

CookingScreen::~CookingScreen() {
	unsubscribe();
}

void CookingScreen::draw(Tmpl8::Surface* surface) {
	auto cauldron = dynamic_cast<CookingCauldron*>(objects_[cauldronId].get());
	cauldron->drawBack(surface);

	Screen::draw(surface);

	cauldron->drawFront(surface);
}

void CookingScreen::process() {
	Screen::process();
}

void CookingScreen::subscribe() {
	Screen::subscribe();

	escapePressedUnsub = escapePressed.subscribe([]() {
		changeScreen.emit(1);
	});

	cauldronInteractedUnsub = cauldronInteracted.subscribe([this]() {
		trackSpoonMovement = true;
	});

	cauldronInteractionEndedUnsub = cauldronInteractionEnded.subscribe([this]() {
		trackSpoonMovement = false;
	});

	blowerInteractedUnsub = blowerInteracted.subscribe([this]() {
		trackBlowerMovement = true;
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {onBlow(delta); });
	});

	blowerInteractionEndedUnsub = blowerInteractionEnded.subscribe([this]() {
		trackBlowerMovement = false;
		blowedSignalUnsub();
	});

	if (trackBlowerMovement) 
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {onBlow(delta); });

	requestMoveUnsub = requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Object& object) {
		Tmpl8::vec2 collides = objectsCollideWithBounds(object, velocity);

		Tmpl8::vec2 newPos = oldPos + newPos;

		if (oldPos != newPos) 
			object.setPos(oldPos + collides);

		interactionCheck(object.getAbsoluteInteractionBounds());

		auto cauldron = dynamic_cast<CookingCauldron*>(objects_[cauldronId].get());
		if (trackSpoonMovement && oldPos != newPos) 
			cauldron->stir(std::abs(collides.x));
	});
}

void CookingScreen::unsubscribe() {
	Screen::unsubscribe();

	escapePressedUnsub();
	cauldronInteractedUnsub();
	cauldronInteractionEndedUnsub();
	blowerInteractedUnsub();
	blowerInteractionEndedUnsub();
	blowedSignalUnsub();
	requestMoveUnsub();
}