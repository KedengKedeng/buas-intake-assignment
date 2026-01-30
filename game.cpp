#include "game.h"
#include "surface.h"
#include "playScreen.hpp"
#include "startScreen.hpp"
#include "settingsScreen.hpp"
#include "cookingScreen.hpp"
#include "inventoryScreen.hpp"
#include "animalShopScreen.hpp"
#include "screenSignals.hpp"
#include "itemList.hpp"
#include "spriteList.hpp"
#include "surfaceList.hpp"
#include "creatureTypeList.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "cauldron.hpp"
#include "wallet.hpp"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		setupSurfaceList();
		setupSpriteList();
		setupItemList();
		setupCreatureTypeList();

		mouseInput = MouseInput();

		std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>();
		std::shared_ptr<Husbandry> husbandry = std::make_shared<Husbandry>();
		std::shared_ptr<Cauldron> cauldron = std::make_shared<Cauldron>();
		std::shared_ptr<Wallet> wallet = std::make_shared<Wallet>();
		husbandry->addPlot(std::make_shared<Plot>(creatureTypeRepository.get(std::string("testAnimal"))));

		screens[Screens::TitleMenu] = std::make_shared<StartScreen>(surface_);
		screens[Screens::Play] = std::make_shared<PlayScreen>(surface_, inventory, husbandry, cauldron);
		screens[Screens::SettingsMenu] = std::make_shared<SettingsScreen>(surface_);
		screens[Screens::Cooking] = std::make_shared<CookingScreen>(surface_, cauldron);
		screens[Screens::Inventory] = std::make_shared<InventoryScreen>(surface_, inventory);
		screens[Screens::AnimalShop] = std::make_shared<AnimalShopScreen>(surface_, wallet, husbandry);

		currentScreens.push_back(screens[Screens::TitleMenu]);
		screens[Screens::TitleMenu]->subscribe();

		pushToCurrentScreenQueue.subscribe([this](std::function<void()> func) {
			currentScreens[0]->pushToQueue(func);
		});

		pushToScreenQueue.subscribe([this](Screens screen, std::function<void()> func) {
			screens[screen]->pushToQueue(func);
		});

		changeScreen.subscribe([this](Screens screen) { 
			queue.push([this, screen]() {
				for (auto& screen : currentScreens) screen->unsubscribe();
				currentScreens.clear();
				currentScreens.push_back(screens[screen]);
				auto screen = currentScreens.end() - 1;
				screen->get()->subscribe();
			});
		});

		stackScreen.subscribe([this](Screens screen) {
			queue.push([this, screen]() {
				for (auto& screen : currentScreens) screen->unsubscribe();
				currentScreens.push_back(screens[screen]);
				auto screen = currentScreens.end() - 1;
				screen->get()->subscribe();
			});
		});

		closeScreen.subscribe([this]() {
			queue.push([this]() {
				(currentScreens.end() - 1)->get()->unsubscribe();
				currentScreens.pop_back();
				(currentScreens.end() - 1)->get()->subscribe();
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
		surface_->Clear(0x6495ED);

		currentScreens[currentScreens.size() - 1]->process(deltaTime);

		for (; !queue.empty(); queue.pop()) {
			auto func = queue.front();
			func();
		}

		for (auto& screen : currentScreens) screen->draw(surface_, vec2(0.0f));
	}
};