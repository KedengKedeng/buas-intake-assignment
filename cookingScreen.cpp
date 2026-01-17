#include "cookingScreen.hpp"
#include "spoon.hpp"
#include "screenSignals.hpp"
#include "objectSignals.hpp"
#include "invisibleBarrier.hpp"
#include "random.hpp"
#include "objectRepository.hpp"
#include "blower.hpp"
#include "screenCommands.hpp"

CookingScreen::CookingScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<ChangeScreenCommand>(Screens::Play); });

	int surfaceWidth = surface->GetWidth();
	int surfaceHeight = surface->GetHeight();

	std::shared_ptr<CookingCauldron> cauldron = std::make_shared<CookingCauldron>(getRandomNum(), std::dynamic_pointer_cast<Cauldron>(objectRepository.get("cauldron")));

	// get a reference of the cauldron for operations on it specifically later
	cauldronId = cauldron->getId();

	cauldron->setPos(vec2<float>(surfaceWidth / 2 - 100, surfaceHeight) - cauldron->getPos());
	auto cauldronSize = cauldron->getSize() + vec2(220, 80);

	// cauldron collision walls
	// the collision system doesnt allow for unique shapes past filled squares right now.
	// so we have to instantiate each side like this outside of the object.
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + vec2(80.0f), vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + vec2(cauldronSize.x - 100, 80.0f), vec2(40.0f, cauldronSize.y - 80)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), cauldron->getPos() + vec2(80.0f, cauldronSize.y - 100), vec2(cauldronSize.x - 140, 1.0f)));

	// screen edge collision walls
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2(0.0f), vec2<float>(1, surfaceHeight)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2<float>(surfaceWidth, 0), vec2<float>(1, surfaceHeight)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2<float>(0, surfaceHeight), vec2<float>(surfaceWidth, 1)));

	// insert main interactable objects
	insertObject(std::make_shared<Spoon>(0, cauldron->getPos() + vec2(cauldronSize.x, 0.0f) / 2));
	insertObject(std::make_shared<Blower>(1, cauldron->getPos() + vec2(500, 180)));
	insertObject(cauldron);
}

CookingScreen::~CookingScreen() {
	unsubscribe();
}

void CookingScreen::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto cauldron = getObject<CookingCauldron>(cauldronId);
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

	unsubscribers.push_back(requestMove.subscribe([this](vec2<float>& oldPos, vec2<float>& velocity, Object& object) {
		auto collides = objectsCollideWithBounds(object, velocity);

		auto newPos = oldPos + collides;

		if (oldPos != newPos) 
			object.setPos(newPos);

		interactionCheck(object);

		auto cauldron = getObject<CookingCauldron>(cauldronId);
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