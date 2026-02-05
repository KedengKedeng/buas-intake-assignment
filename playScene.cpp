#include "playScene.hpp"
#include "objectSignals.hpp"
#include "wall.hpp"
#include "worldCauldron.hpp"
#include "itemObject.hpp"
#include "itemSignals.hpp"
#include "keyboardSignals.hpp"
#include "sceneSignals.hpp"
#include "moveCommand.hpp"
#include "interactionCommand.hpp"
#include "sceneCommands.hpp"
#include "spriteRepository.hpp"
#include "plotObject.hpp"
#include "text.hpp"
#include <format>

const float floorScale = 1.5f;
const float tileSize = 32 * floorScale;
const vec2<float> PLOT_SIZE = { tileSize * 8, tileSize * 8 };
const vec2<float> PLOT_MARGINS = { tileSize * 3, tileSize * 3 };

PlayScene::PlayScene(
	Tmpl8::Surface* surface, 
	std::shared_ptr<Inventory> inventory, 
	std::shared_ptr<Husbandry> husbandry, 
	std::shared_ptr<Cauldron> cauldron,
	std::shared_ptr<Wallet> wallet
) :
	Scene(surface), 
	player_(0, vec2(100.0f)), 
	inventory_(inventory), 
	husbandry_(husbandry),
	wallet_(wallet),
	floorTiles_(spriteRepository().getSheet(SpriteSheets::Floor), floorScale)
{
	keyboardInput_.registerHandler(KeyFunctions::WalkLeft, []() {return std::make_unique<MoveCommand>(vec2<int8_t>(-1, 0)); });
	keyboardInput_.registerHandler(KeyFunctions::WalkUp, []() {return std::make_unique<MoveCommand>(vec2<int8_t>(0, -1)); });
	keyboardInput_.registerHandler(KeyFunctions::WalkDown, []() {return std::make_unique<MoveCommand>(vec2<int8_t>(0, 1)); });
	keyboardInput_.registerHandler(KeyFunctions::WalkRight, []() {return std::make_unique<MoveCommand>(vec2<int8_t>(1, 0)); });
	keyboardInput_.registerHandler(KeyFunctions::Interact, []() {return std::make_unique<InteractionCommand>(); });
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<StackSceneCommand>(Scenes::SettingsMenu); });
	keyboardInput_.registerHandler(KeyFunctions::Inventory, []() {return std::make_unique<StackSceneCommand>(Scenes::Inventory); });
	keyboardInput_.registerHandler(KeyFunctions::OpenShop, []() {return std::make_unique<StackSceneCommand>(Scenes::AnimalShop); });

	auto& plots = husbandry_->getPlots();
	vec2 plotSpace(PLOT_MARGINS.x, (PLOT_SIZE.y + PLOT_MARGINS.y) * ceil(plots.size() / 2.0f));
	vec2 roomSize(tileSize * 16, tileSize * 10);

	createPlotObjects(husbandry, vec2(-PLOT_MARGINS.x, -roomSize.y));
	createWorldBounds(-plotSpace, roomSize + plotSpace);

	// interactable objects
	insertObject(std::make_shared<WorldCauldron>(getRandomNum(), vec2(surface->GetWidth() / 2.0f, surface->GetHeight() / 2.0f), cauldron));

	std::vector<FloorTiles> tileTypes { FloorTiles::Ground1, FloorTiles::Ground2, FloorTiles::Ground3, FloorTiles::Ground4 };
	floorTiles_.setSquare(Rect2<int>(-plotSpace.x, -plotSpace.y, roomSize.x + plotSpace.x, roomSize.y + plotSpace.y) / tileSize, tileTypes);
}

void PlayScene::createPlotObjects(std::shared_ptr<Husbandry> husbandry, vec2<float> pos) {
	auto& plots = husbandry->getPlots();
	int plotsPerRow = static_cast<int>(ceil(plots.size() / 2.0f));
	vec2 currentPos = pos;
	int currentPlot = 0;
	for (auto& plot : plots) {
		if (currentPlot == plotsPerRow) {
			currentPos = pos;
			currentPos.x += PLOT_MARGINS.x + PLOT_SIZE.x;
		}
		insertObject(std::make_shared<PlotObject>(getRandomNum(), currentPos, PLOT_SIZE, plot, inventory_, husbandry_));
		currentPos.y -= (PLOT_SIZE.y + PLOT_MARGINS.y); 
		currentPlot++;
	}
}

void PlayScene::createWorldBounds(vec2<float> pos, vec2<float> size) {
	insertObject(std::make_shared<Wall>(getRandomNum(), pos, vec2(1.0f, size.y)));
	insertObject(std::make_shared<Wall>(getRandomNum(), pos, vec2(size.x, 1.0f)));
	insertObject(std::make_shared<Wall>(getRandomNum(), vec2(pos.x, pos.y + size.y), vec2(size.x, 1.0f)));
	insertObject(std::make_shared<Wall>(getRandomNum(), vec2(pos.x + size.x, pos.y), vec2(1.0f, size.y)));
}

void PlayScene::draw(Tmpl8::Surface* surface, vec2<float> offset) const {
	surface->Clear(0x00);

	auto playerSize = player_.getColliderSize();
	auto drawOffset = player_.getPos() - (vec2(surface->GetWidth(), surface->GetHeight()) - vec2(playerSize.width, playerSize.height)) / 2;

	floorTiles_.draw(surface, -drawOffset);
	Scene::draw(surface, -drawOffset);
	player_.draw(surface, -drawOffset);

	drawDispatcher_.draw(surface, -drawOffset);

	Text walletText(std::format("money: {}", wallet_->getCurrency()), 2, 0xff000000);
	surface->Bar(vec2(0.0f), vec2<float>(walletText.getWidth(), walletText.getHeight()), 0xffffffff);
	walletText.draw(surface, vec2(0.0f));
}

void PlayScene::process(float deltaTime) {
	player_.process(deltaTime);

	Scene::process(deltaTime);
}

void PlayScene::subscribe() {
	Scene::subscribe();

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
		stackScene.emit(Scenes::SettingsMenu);
	}));

	addSubscription(cauldronInteracted.subscribe([this]() {
		changeScene.emit(Scenes::Cooking);
	}));
}

void PlayScene::unsubscribe() {
	Scene::unsubscribe();

	player_.unsubscribe();
}