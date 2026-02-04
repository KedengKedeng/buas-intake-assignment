#include "playScreen.hpp"
#include "objectSignals.hpp"
#include "wall.hpp"
#include "worldCauldron.hpp"
#include "itemObject.hpp"
#include "itemSignals.hpp"
#include "keyboardSignals.hpp"
#include "screenSignals.hpp"
#include "moveCommand.hpp"
#include "interactionCommand.hpp"
#include "screenCommands.hpp"
#include "spriteRepository.hpp"
#include "plotObject.hpp"

const float floorScale = 1.5f;
const float tileSize = 32 * floorScale;
const vec2<float> PLOT_SIZE = { tileSize * 8, tileSize * 8 };
const vec2<float> PLOT_MARGINS = { tileSize * 2, tileSize * 2 };

PlayScreen::PlayScreen(
	Tmpl8::Surface* surface, 
	std::shared_ptr<Inventory> inventory, 
	std::shared_ptr<Husbandry> husbandry, 
	std::shared_ptr<Cauldron> cauldron
) :
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
	keyboardInput_.registerHandler("openShop", []() {return std::make_unique<StackScreenCommand>(Screens::AnimalShop); });

	auto& plots = husbandry_->getPlots();
	vec2 plotSpace(0.0f, (PLOT_SIZE.y + PLOT_MARGINS.y) * ceil(plots.size() / 2.0f));
	vec2 roomSize(tileSize * 16, tileSize * 10);

	createPlotObjects(husbandry, -plotSpace);
	createWorldBounds(-plotSpace, roomSize + plotSpace);

	// interactable objects
	insertObject(std::make_shared<WorldCauldron>(getRandomNum(), vec2(surface->GetWidth() / 2.0f, surface->GetHeight() / 2.0f), cauldron));

	std::vector<FloorTiles> tileTypes { FloorTiles::Ground1, FloorTiles::Ground2, FloorTiles::Ground3, FloorTiles::Ground4 };
	floorTiles_.setSquare(Rect2<int>(-plotSpace.x, -plotSpace.y, roomSize.x + plotSpace.x, roomSize.y + plotSpace.y) / tileSize, tileTypes);
}

void PlayScreen::createPlotObjects(std::shared_ptr<Husbandry> husbandry, const vec2<float>& pos) {
	auto& plots = husbandry->getPlots();
	int plotsPerRow = static_cast<int>(ceil(plots.size() / 2.0f));
	vec2 currentPos = pos;
	int currentPlot = 0;
	for (auto& plot : plots) {
		insertObject(std::make_shared<PlotObject>(getRandomNum(), currentPos, PLOT_SIZE, plot, inventory_, husbandry_));
		if (currentPlot == plotsPerRow) {
			currentPos = pos + PLOT_SIZE;
			currentPos.x += PLOT_MARGINS.x;
		}
		currentPos.y -= PLOT_SIZE.y - PLOT_MARGINS.y; 
		currentPlot++;
	}
}

void PlayScreen::createWorldBounds(const vec2<float>& pos, const vec2<float>& size) {
	insertObject(std::make_shared<Wall>(getRandomNum(), pos, vec2(1.0f, size.y)));
	insertObject(std::make_shared<Wall>(getRandomNum(), pos, vec2(size.x, 1.0f)));
	insertObject(std::make_shared<Wall>(getRandomNum(), vec2(pos.x, pos.y + size.y), vec2(size.x, 1.0f)));
	insertObject(std::make_shared<Wall>(getRandomNum(), vec2(pos.x + size.x, pos.y), vec2(1.0f, size.y)));
}

void PlayScreen::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	surface->Clear(0x00);
	auto playerSize = player_.getColliderSize();
	auto drawOffset = player_.getPos() - (vec2(surface->GetWidth(), surface->GetHeight()) - vec2(playerSize.width, playerSize.height)) / 2;
	floorTiles_.draw(surface, -drawOffset);
	Screen::draw(surface, -drawOffset);
	player_.draw(surface, -drawOffset);
	drawDispatcher_.draw(surface, -drawOffset);
}

void PlayScreen::process(float deltaTime) {
	player_.process(deltaTime);

	Screen::process(deltaTime);
}

void PlayScreen::subscribe() {
	Screen::subscribe();

	player_.subscribe();

	addSubscription(itemPickedUp.subscribe([this](std::shared_ptr<Item> item) {
		inventory_->add(item->name);
	}));

	addSubscription(itemDroppedFromInventory.subscribe([this](std::shared_ptr<Item> item) {
		// drop item on the ground if nothing is checking to pick it up
		if (itemDropped.getListenerCount() == 0) {
			std::shared_ptr<ItemObject> itemObject = std::make_shared<ItemObject>(getRandomNum(), player_.getPos(), item);
			itemObject->subscribe();
			insertObject(itemObject);
		}
		// otherwise allow said listener to pick up the item
		else itemDropped.emit(item);
	}));

	addSubscription(requestMove.subscribe([this](vec2<float>& oldPos, vec2<float>& velocity, Object& object) {
		auto collides = objectsCollideWithBounds(object, velocity);

		vec2<float> newPos = oldPos + collides;

		if (oldPos != newPos) 
			object.setPos(newPos);

		interactionCheck(object);
	}));

	addSubscription(escapePressed.subscribe([]() {
		stackScreen.emit(Screens::SettingsMenu);
	}));

	addSubscription(cauldronInteracted.subscribe([this]() {
		changeScreen.emit(Screens::Cooking);
	}));
}

void PlayScreen::unsubscribe() {
	Screen::unsubscribe();

	player_.unsubscribe();
}