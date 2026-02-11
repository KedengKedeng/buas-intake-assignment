#include "game.h"
#include "itemList.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "cauldron.hpp"
#include "wallet.hpp"
#include "itemLog.hpp"
#include "creatureTypeRepository.hpp"
#include "playScene.hpp"
#include "startScene.hpp"
#include "settingsScene.hpp"
#include "cookingScene.hpp"
#include "inventoryScene.hpp"
#include "animalShopScene.hpp"
#include "sceneSignals.hpp"


namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		setupRecipeList();

		std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>();
		std::shared_ptr<Husbandry> husbandry = std::make_shared<Husbandry>();
		std::shared_ptr<Cauldron> cauldron = std::make_shared<Cauldron>();
		std::shared_ptr<Wallet> wallet = std::make_shared<Wallet>();
		std::shared_ptr<ItemLog> itemLog = std::make_shared<ItemLog>();
		// if we dont log this at the start customers cant ask for any items at all
		itemLog->logItem(Items::BlueSlime);

		for (int x = static_cast<int>(CreatureTypes::FIRST); x != static_cast<int>(CreatureTypes::LAST); x++)
			husbandry->addPlot(std::make_shared<Plot>(creatureTypeRepository().get(CreatureTypes(x))));

		// init all scenes
		int width = surface_.GetWidth();
		int height = surface_.GetHeight();
		scenes[Scenes::TitleMenu] = std::make_shared<StartScene>(width, height);
		scenes[Scenes::Play] = std::make_shared<PlayScene>(width, height, inventory, husbandry, cauldron, wallet, itemLog);
		scenes[Scenes::SettingsMenu] = std::make_shared<SettingsScene>(width, height);
		scenes[Scenes::Cooking] = std::make_shared<CookingScene>(width, height, cauldron, inventory);
		scenes[Scenes::Inventory] = std::make_shared<InventoryScene>(width, height, inventory);
		scenes[Scenes::AnimalShop] = std::make_shared<AnimalShopScene>(width, height, wallet, husbandry, itemLog);

		// set title menu as start scene
		currentScenes.push_back(scenes[Scenes::TitleMenu]);
		scenes[Scenes::TitleMenu]->subscribe();

		pushToCurrentSceneQueue.subscribe([this](std::function<void()> func) {
			currentScenes[0]->pushToQueue(func);
		});

		pushToSceneQueue.subscribe([this](Scenes scene, std::function<void()> func) {
			scenes[scene]->pushToQueue(func);
		});

		changeScene.subscribe([this](Scenes scene) { 
			queue.push([this, scene]() {
				for (auto& scene : currentScenes) scene->unsubscribe();
				currentScenes.clear();
				currentScenes.push_back(scenes[scene]);
				auto scene = currentScenes.end() - 1;
				scene->get()->subscribe();
			});
		});

		stackScene.subscribe([this](Scenes scene) {
			queue.push([this, scene]() {
				for (auto& scene : currentScenes) scene->unsubscribe();
				currentScenes.push_back(scenes[scene]);
				auto scene = currentScenes.end() - 1;
				scene->get()->subscribe();
			});
		});

		closeScene.subscribe([this]() {
			queue.push([this]() {
				(currentScenes.end() - 1)->get()->unsubscribe();
				currentScenes.pop_back();
				(currentScenes.end() - 1)->get()->subscribe();
			});
		});
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		surface_.Clear(0xFF6495ED);

		currentScenes[currentScenes.size() - 1]->process(deltaTime);

		// in case of scene switches we want the current scene to first finish processing
		// and then switch. hence this queue.
		for (; !queue.empty(); queue.pop()) {
			auto func = queue.front();
			func();
		}

		for (auto& scene : currentScenes) scene->draw(surface_, vec2(0.0f));
	}
};