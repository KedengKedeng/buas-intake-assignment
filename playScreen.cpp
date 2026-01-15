#include "playScreen.hpp"
#include "objectSignals.hpp"
#include "wall.hpp"
#include "worldCauldron.hpp"
#include "itemObject.hpp"
#include "itemSignals.hpp"
#include "interactionSignal.hpp"
#include "itemsRepository.hpp"
#include "keyboardSignals.hpp"
#include "screenSignals.hpp"
#include "objectRepository.hpp"
#include "moveCommand.hpp"
#include "interactionCommand.hpp"
#include "screenCommands.hpp"
#include "spriteRepository.hpp"

const float floorScale = 1.5f;
const float tileSize = 32 * floorScale;
const vec2<float> PLOT_SIZE = { tileSize * 8, tileSize * 8 };
const vec2<float> PLOT_MARGINS = { tileSize * 2, tileSize * 2 };

PlayScreen::PlayScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory, std::shared_ptr<Husbandry> husbandry) : 
	Screen(surface), 
	player_(0, vec2(100.0f)), 
	inventory_(inventory), 
	husbandry_(husbandry),
	floorTiles_(spriteRepository.getSheet("floor"), floorScale)
{
	keyboardInput_.registerHandler("walkLeft", []() {return std::make_unique<MoveCommand>(vec2<int8_t>(-1, 0)); });
	keyboardInput_.registerHandler("walkUp", []() {return std::make_unique<MoveCommand>(vec2<int8_t>(0, -1)); });
	keyboardInput_.registerHandler("walkDown", []() {return std::make_unique<MoveCommand>(vec2<int8_t>(0, 1)); });
	keyboardInput_.registerHandler("walkRight", []() {return std::make_unique<MoveCommand>(vec2<int8_t>(1, 0)); });
	keyboardInput_.registerHandler("interact", []() {return std::make_unique<InteractionCommand>(); });
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<StackScreenCommand>(Screens::SettingsMenu); });
	keyboardInput_.registerHandler("inventory", []() {return std::make_unique<StackScreenCommand>(Screens::Inventory); });

	auto& plots = husbandry_->getPlots();
	vec2 plotSpace(0.0f, (PLOT_SIZE.y + PLOT_MARGINS.y) * ceil(plots.size() / 2.0f));
	vec2 roomSize(tileSize * 16, tileSize * 10);

	createWorldBounds(-plotSpace, roomSize + plotSpace);

	// interactable objects
	insertObject(std::make_shared<WorldCauldron>(getRandomNum(), vec2(surface->GetWidth() / 2.0f, surface->GetHeight() / 2.0f), std::dynamic_pointer_cast<Cauldron>(objectRepository.get("cauldron"))));
	insertObject(std::make_shared<ItemObject>(getRandomNum(), vec2(20.0f, 50.0f), itemRepository.get("testItem")));

	std::vector<FloorTiles> tileTypes { FloorTiles::Ground1, FloorTiles::Ground2, FloorTiles::Ground3, FloorTiles::Ground4 };
	floorTiles_.setSquare(Rect2<int>(-plotSpace.x, -plotSpace.y, roomSize.x + plotSpace.x, roomSize.y + plotSpace.y) / tileSize, tileTypes);
}

PlayScreen::~PlayScreen() {
	unsubscribe();
}

void PlayScreen::createWorldBounds(const vec2<float>& pos, const vec2<float>& size) {
	insertObject(std::make_shared<Wall>(getRandomNum(), pos, vec2(1.0f, size.y)));
	insertObject(std::make_shared<Wall>(getRandomNum(), pos, vec2(size.x, 1.0f)));
	insertObject(std::make_shared<Wall>(getRandomNum(), vec2(pos.x, pos.y + size.y), vec2(size.x, 1.0f)));
	insertObject(std::make_shared<Wall>(getRandomNum(), vec2(pos.x + size.x, pos.y), vec2(1.0f, size.y)));
}

void PlayScreen::deleteObject(int64_t id) {
	objects_.erase(id);
}

void PlayScreen::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Clear(0x00);
	auto drawOffset = player_.getPos() - (vec2(surface->GetWidth(), surface->GetHeight()) - player_.getColliderSize()) / 2;
	floorTiles_.draw(surface, -drawOffset);
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
			std::shared_ptr<ItemObject> itemObject = std::make_shared<ItemObject>(getRandomNum(), player_.getPos(), item);
			itemObject->subscribe();
			insertObject(itemObject);
		}
		// otherwise allow said listener to pick up the item
		else itemDropped.emit(item);
	}));

	unsubscribers.push_back(requestMove.subscribe([this](vec2<float>& oldPos, vec2<float>& velocity, Object& object) {
		auto collides = objectsCollideWithBounds(object, velocity);

		vec2<float> newPos = oldPos + collides;

		if (oldPos != newPos) 
			object.setPos(newPos);

		interactionCheck(object);
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