#include "cookingScene.hpp"
#include "spoon.hpp"
#include "sceneSignals.hpp"
#include "objectSignals.hpp"
#include "invisibleBarrier.hpp"
#include "random.hpp"
#include "blower.hpp"
#include "sceneCommands.hpp"
#include "cookingCauldron.hpp"

CookingScene::CookingScene(Tmpl8::Surface& surface, std::shared_ptr<Cauldron> cauldron, std::shared_ptr<Inventory> inventory) : 
	Scene(surface),
	inventory_(inventory),
	cauldron_(cauldron)
{
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<ChangeSceneCommand>(Scenes::Play); });
	keyboardInput_.registerHandler(KeyFunctions::ResetCauldron, [this]() {
		auto& items = cauldron_->getItems();
		for (auto& item : items) inventory_->add(item->id);
		cauldron_->reset();
		return std::make_unique<Command>();
	});

	int surfaceWidth = surface.GetWidth();
	int surfaceHeight = surface.GetHeight();

	std::shared_ptr<CookingCauldron> cookingCauldron = std::make_shared<CookingCauldron>(getRandomNum(), cauldron);

	// get a reference of the cauldron for operations on it specifically later
	cauldronId = cookingCauldron->getId();

	cookingCauldron->setPos(vec2<float>(surfaceWidth / 2 - 100, surfaceHeight) - cookingCauldron->getPos());

	// scene edge collision walls
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2(0.0f), vec2<float>(1, surfaceHeight)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2<float>(surfaceWidth, 0), vec2<float>(1, surfaceHeight)));
	insertObject(std::make_shared<InvisibleBarrier>(getRandomNum(), vec2<float>(0, surfaceHeight), vec2<float>(surfaceWidth, 1)));

	// insert main interactable objects
	insertObject(std::make_shared<Spoon>(0, cookingCauldron->getPos() + vec2(cookingCauldron->getSize().x, -200.0f) / 2));
	insertObject(std::make_shared<Blower>(1, cookingCauldron->getPos() + vec2(500, 180)));
	insertObject(cookingCauldron);
}

void CookingScene::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	auto cauldron = getObject<CookingCauldron>(cauldronId);
	cauldron->drawBack(surface, offset);

	Scene::draw(surface, offset);

	cauldron->drawFront(surface, offset);
}

void CookingScene::subscribe() {
	Scene::subscribe();

	addSubscription(cauldronInteracted.subscribe([this]() {
		trackSpoonMovement = true;
	}));

	addSubscription(cauldronInteractionEnded.subscribe([this]() {
		trackSpoonMovement = false;
	}));

	addSubscription(blowerInteracted.subscribe([this]() {
		trackBlowerMovement = true;
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {cauldron_->addTemp(delta); });
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

		if (trackSpoonMovement && collides != vec2(0.0f)) {
			auto output = cauldron_->stir(std::abs(collides.x));
			if (output != nullptr) inventory_->add(output->id);
		}
	}));

	// Only subscribe if the blower is being interacted with
	if (trackBlowerMovement)
		blowedSignalUnsub = blowedSignal.subscribe([this](float delta) {cauldron_->addTemp(delta); });

	addSubscription([this]() {blowedSignalUnsub(); });
}