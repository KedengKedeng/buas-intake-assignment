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

const Tmpl8::vec2 PLOT_SIZE = { 300, 300 };
const Tmpl8::vec2 PLOT_MARGINS = { 50, 50 };

PlayScreen::PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory, std::shared_ptr<Husbandry> husbandry)
	: Screen(surface), player_(0, Tmpl8::vec2(100, 100)), inventory_(inventory), husbandry_(husbandry) {
	keyboardInput_.registerHandler("walkLeft", []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ -1, 0 }); });
	keyboardInput_.registerHandler("walkUp", []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ 0, -1 }); });
	keyboardInput_.registerHandler("walkDown", []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ 0, 1 }); });
	keyboardInput_.registerHandler("walkRight", []() {return std::make_unique<MoveCommand>(Tmpl8::vec2{ 1, 0 }); });
	keyboardInput_.registerHandler("interact", []() {return std::make_unique<InteractionCommand>(); });
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<StackScreenCommand>(Screens::SettingsMenu); });
	keyboardInput_.registerHandler("inventory", []() {return std::make_unique<StackScreenCommand>(Screens::Inventory); });

	auto& plots = husbandry_->getPlots();
	Tmpl8::vec2 plotSpace = Tmpl8::vec2(10.0f, (PLOT_SIZE.y + PLOT_MARGINS.y) * ceil(plots.size() / 2.0f));

	createWorldBounds(-plotSpace, Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) + plotSpace);

	// interactable objects
	insertObject(std::make_unique<WorldCauldron>(getRandomNum(), Tmpl8::vec2(surface->GetWidth() / 2, surface->GetHeight() / 2), std::dynamic_pointer_cast<Cauldron>(objectRepository.get("cauldron"))));
	insertObject(std::make_unique<ItemObject>(getRandomNum(), Tmpl8::vec2(20, 50), itemRepository.get("testItem")));
}

PlayScreen::~PlayScreen() {
	unsubscribe();
}

void PlayScreen::createWorldBounds(const Tmpl8::vec2& pos, const Tmpl8::vec2& size) {
	insertObject(std::make_unique<Wall>(getRandomNum(), pos, Tmpl8::vec2(1.0f, size.y)));
	insertObject(std::make_unique<Wall>(getRandomNum(), pos, Tmpl8::vec2(size.x, 1.0f)));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(pos.x, pos.y + size.y), Tmpl8::vec2(size.x, 1.0f)));
	insertObject(std::make_unique<Wall>(getRandomNum(), Tmpl8::vec2(pos.x + size.x, pos.y), Tmpl8::vec2(1.0f, size.y)));
}

void PlayScreen::deleteObject(int64_t id) {
	objects_.erase(id);
}

void PlayScreen::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	auto drawOffset = player_.getPos() - (Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) - player_.getBounds().getSize()) / 2;
	Screen::draw(surface, -drawOffset);
	player_.draw(surface, -drawOffset);
}

void PlayScreen::process(float deltaTime) {
	player_.process(deltaTime);

	Screen::process(deltaTime);
}

void PlayScreen::subscribe() {
	Screen::subscribe();

	player_.subscribe();

	unsubscribers.push_back(deleteObjectSignal.subscribe([this](int64_t id) {
		queue.push([this, id]() {deleteObject(id); });
	}));

	unsubscribers.push_back(itemPickedUp.subscribe([this](std::shared_ptr<Item> item) {
		inventory_->add(item->name);
	}));

	unsubscribers.push_back(itemDroppedFromInventory.subscribe([this](std::shared_ptr<Item> item) {
		// drop item on the ground if nothing is checking to pick it up
		if (itemDropped.getListenerCount() == 0) {
			std::unique_ptr<ItemObject> itemObject = std::make_unique<ItemObject>(getRandomNum(), player_.getPos(), item);
			itemObject->subscribe();
			insertObject(std::move(itemObject));
		}
		// otherwise allow said listener to pick up the item
		else itemDropped.emit(item);
	}));

	unsubscribers.push_back(requestMove.subscribe([this](Tmpl8::vec2& oldPos, Tmpl8::vec2& velocity, Object& object) {
		Tmpl8::vec2 collides = objectsCollideWithBounds(object, velocity);

		Tmpl8::vec2 newPos = oldPos + newPos;

		if (oldPos != newPos) 
			object.setPos(oldPos + collides);

		if (object.isInteractor()) interactionCheck(object.getAbsoluteInteractionBounds());
	}));

	unsubscribers.push_back(escapePressed.subscribe([]() {
		stackScreen.emit(Screens::SettingsMenu);
	}));

	unsubscribers.push_back(cauldronInteracted.subscribe([this]() {
		changeScreen.emit(Screens::Cooking);
	}));
}

void PlayScreen::unsubscribe() {
	Screen::unsubscribe();

	player_.unsubscribe();
}