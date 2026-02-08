#include "game.h"
#include "surface.h"
#include "playScene.hpp"
#include "startScene.hpp"
#include "settingsScene.hpp"
#include "cookingScene.hpp"
#include "inventoryScene.hpp"
#include "animalShopScene.hpp"
#include "sceneSignals.hpp"
#include "itemList.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "cauldron.hpp"
#include "wallet.hpp"
#include "creatureTypeRepository.hpp"

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

		for (int x = static_cast<int>(CreatureTypes::FIRST); x != static_cast<int>(CreatureTypes::LAST); x++)
			husbandry->addPlot(std::make_shared<Plot>(creatureTypeRepository().get(CreatureTypes(x))));

		// init all scenes
		scenes[Scenes::TitleMenu] = std::make_shared<StartScene>(surface_);
		scenes[Scenes::Play] = std::make_shared<PlayScene>(surface_, inventory, husbandry, cauldron, wallet);
		scenes[Scenes::SettingsMenu] = std::make_shared<SettingsScene>(surface_);
		scenes[Scenes::Cooking] = std::make_shared<CookingScene>(surface_, cauldron, inventory);
		scenes[Scenes::Inventory] = std::make_shared<InventoryScene>(surface_, inventory);
		scenes[Scenes::AnimalShop] = std::make_shared<AnimalShopScene>(surface_, wallet, husbandry);

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
		surface_->Clear(0xFF6495ED);

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