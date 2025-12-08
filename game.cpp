#include "game.h"
#include "surface.h"
#include "button.hpp"
#include "playScreen.hpp"
#include "startScreen.hpp"
#include "settingsScreen.hpp"
#include "cookingScreen.hpp"
#include "screenSignals.hpp"
#include "itemList.hpp"
#include "spriteList.hpp"
#include "objectList.hpp"

extern void setupObjectList();

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		setupSpriteList();
		setupItemList();
		setupObjectList();

		keyboardInput = KeyboardInput();
		mouseInput = MouseInput();

		screens[Screens::TitleMenu] = std::make_shared<StartScreen>(surface_);
		screens[Screens::Play] = std::make_shared<PlayScreen>(surface_);
		screens[Screens::SettingsMenu] = std::make_shared<SettingsScreen>(surface_);
		screens[Screens::Cooking] = std::make_shared<CookingScreen>(surface_);
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
				currentScreens[0]->subscribe();
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

	static int frame = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		surface_->Clear(255 << 8);

		for (auto& screen : currentScreens) screen->process();

		for (; !queue.empty(); queue.pop()) {
			auto func = queue.front();
			func();
		}

		for (auto& screen : currentScreens) screen->draw(surface_);
	}
};