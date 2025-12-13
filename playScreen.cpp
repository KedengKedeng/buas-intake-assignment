#include "playScreen.hpp"
#include "objectSignals.hpp"
#include "wall.hpp"
#include "worldCauldron.hpp"
#include "itemObject.hpp"
#include "sprite.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "itemsRepository.hpp"
#include "keyboardSignals.hpp"
#include "screenSignals.hpp"
#include "objectRepository.hpp"
#include "moveCommand.hpp"
#include "interactionCommand.hpp"
#include "screenCommands.hpp"

PlayScreen::PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory) 
	: Screen(surface), player_(0, Tmpl8::vec2(100, 100)), inventory_(inventory) {
	keyboardInput_.registerHandler(std::string("walkLeft"), []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ -1, 0 }); });
	keyboardInput_.registerHandler(std::string("walkUp"), []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ 0, -1 }); });
	keyboardInput_.registerHandler(std::string("walkDown"), []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ 0, 1 }); });
	keyboardInput_.registerHandler(std::string("walkRight"), []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ 1, 0 }); });
	keyboardInput_.registerHandler(std::string("interact"), []() {return std::make_unique<InteractionCommand>(); });
	keyboardInput_.registerHandler(std::string("escape"), []() {return std::make_unique<StackScreenCommand>(Screens::SettingsMenu); });
	keyboardInput_.registerHandler(std::string("inventory"), []() {return std::make_unique<StackScreenCommand>(Screens::Inventory); });

	// world boundaries
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(0), Tmpl8::vec2(1, surface->GetHeight())));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(0), Tmpl8::vec2(surface->GetWidth(), 1)));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(0, surface->GetHeight() - 1), Tmpl8::vec2(surface->GetWidth(), 1)));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(surface->GetWidth() - 1, 0), Tmpl8::vec2(1, surface->GetHeight())));

	// interactable objects
	insertObject(std::make_unique<WorldCauldron>(getRandomNum(), Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight() / 2), std::dynamic_pointer_cast<Cauldron>(objectRepository.get(std::string("cauldron")))));
	insertObject(std::make_unique<ItemObject>(getRandomNum(), Tmpl8::vec2(20, 50), itemRepository.get(std::string("testItem"))));
}

PlayScreen::~PlayScreen() {
	unsubscribe();
}

void PlayScreen::deleteObject(int64_t id) {
	objects_.erase(id);
}

void PlayScreen::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	auto drawOffset = player_.getPos() - (Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) - player_.getBounds().getSize()) / 2;
	Screen::draw(surface, -drawOffset);
	player_.draw(surface, -drawOffset);
}

void PlayScreen::process() {
	player_.process();

	Screen::process();
}

void PlayScreen::subscribe() {
	Screen::subscribe();

	player_.subscribe();

	deleteObjectSignalUnsub = deleteObjectSignal.subscribe([this](int64_t id) {
		queue.push([this, id]() {deleteObject(id); });
	});

	itemPickedUpUnsub = itemPickedUp.subscribe([this](std::shared_ptr<Item> item) {
		inventory_->addItem(item->name);
	});

	itemDroppedUnsub = itemDroppedFromInventory.subscribe([this](std::shared_ptr<Item> item) {
		// drop item on the ground if nothing is checking to pick it up
		if (itemDropped.getListenerCount() == 0) {
			std::unique_ptr<ItemObject> itemObject = std::make_unique<ItemObject>(getRandomNum(), player_.getPos(), item);
			itemObject->subscribe();
			insertObject(std::move(itemObject));
		}
		// otherwise allow said listener to pick up the item
		else itemDropped.emit(item);
	});

	requestMoveUnsub = requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Object& object) {
		Tmpl8::vec2 collides = objectsCollideWithBounds(object, velocity);

		Tmpl8::vec2 newPos = oldPos + newPos;

		if (oldPos != newPos) 
			object.setPos(oldPos + collides);

		interactionCheck(object.getAbsoluteInteractionBounds());
	});

	escapePressedUnsub = escapePressed.subscribe([]() {
		stackScreen.emit(Screens::SettingsMenu);
	});

	cauldronInteractedUnsub = cauldronInteracted.subscribe([this]() {
		changeScreen.emit(Screens::Cooking);
	});
}

void PlayScreen::unsubscribe() {
	Screen::unsubscribe();

	player_.unsubscribe();

	deleteObjectSignalUnsub();
	itemPickedUpUnsub();
	itemDroppedUnsub();
	requestMoveUnsub();
	escapePressedUnsub();
	cauldronInteractedUnsub();
}