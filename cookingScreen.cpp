#include "cookingScreen.hpp"
#include "spoon.hpp"
#include "screenSignals.hpp"
#include "objectSignals.hpp"
#include "invisibleBarrier.hpp"
#include "random.hpp"
#include "blower.hpp"
#include "screenCommands.hpp"

CookingScreen::CookingScreen(Tmpl8::Surface* surface, std::shared_ptr<Cauldron> cauldron) : Screen(surface) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<ChangeScreenCommand>(Screens::Play); });

	int surfaceWidth = surface->GetWidth();
	int surfaceHeight = surface->GetHeight();

	std::shared_ptr<CookingCauldron> cookingCauldron = std::make_shared<CookingCauldron>(getRandomNum(), cauldron);

	// get a reference of the cauldron for operations on it specifically later
	cauldronId = cookingCauldron->getId();

	cookingCauldron->setPos(vec2<float>(surfaceWidth / 2 - 100, surfaceHeight) - cookingCauldron->getPos());

	// screen edge collision walls
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2(0.0f), vec2<float>(1, surfaceHeight)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2<float>(surfaceWidth, 0), vec2<float>(1, surfaceHeight)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2<float>(0, surfaceHeight), vec2<float>(surfaceWidth, 1)));

	// insert main interactable objects
	insertObject(std::make_shared<Spoon>(0, cookingCauldron->getPos() + vec2(cookingCauldron->getSize().x, -50.0f) / 2));
	insertObject(std::make_shared<Blower>(1, cookingCauldron->getPos() + vec2(500, 180)));
	insertObject(cookingCauldron);
}

void CookingScreen::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto cauldron = getObject<CookingCauldron>(cauldronId);
	cauldron->drawBack(surface);

	Screen::draw(surface, offset);

	cauldron->drawFront(surface);
}

void CookingScreen::subscribe() {
	Screen::subscribe();

	addSubscription(cauldronInteracted.subscribe([this]() {
		trackSpoonMovement = true;
	}));

	addSubscription(cauldronInteractionEnded.subscribe([this]() {
		trackSpoonMovement = false;
	}));

	addSubscription(blowerInteracted.subscribe([this]() {
		trackBlowerMovement = true;
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {onBlow(delta); });
	}));

	addSubscription(blowerInteractionEnded.subscribe([this]() {
		trackBlowerMovement = false;
		blowedSignalUnsub();
	}));

	addSubscription(requestMove.subscribe([this](vec2<float>& oldPos, vec2<float>& velocity, Object& object) {
		auto collides = objectsCollideWithBounds(object, velocity);

		auto newPos = oldPos + collides;

		if (oldPos != newPos) 
			object.setPos(newPos);

		interactionCheck(object);

		auto cauldron = getObject<CookingCauldron>(cauldronId);
		if (trackSpoonMovement && collides != vec2(0.0f)) 
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