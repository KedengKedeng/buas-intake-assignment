#include "game.h"
#include "surface.h"
#include "button.hpp"
#include "playScreen.hpp"
#include "startScreen.hpp"
#include "screenSignals.hpp"
#include "itemList.hpp"
#include "spriteList.hpp"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		setupSpriteList();
		setupItemList();

		keyboardInput = KeyboardInput();
		mouseInput = MouseInput();

		screens[0] = std::make_shared<StartScreen>(surface_);
		screens[1] = std::make_shared<PlayScreen>(surface_);
		currentScreens.push_back(screens[0]);
		screens[0]->subscribe();

		changeScreen.subscribe([this](int screenIndex) { 
			queue.push([this, screenIndex]() {
				for (auto& screen : currentScreens) screen->unsubscribe();
				currentScreens.clear();
				currentScreens.push_back(screens[screenIndex]);
				currentScreens[0]->subscribe();
			});
		});

		stackScreen.subscribe([this](int screenIndex) {
			queue.push([this, screenIndex]() {
				for (auto& screen : currentScreens) screen->unsubscribe();
				currentScreens.push_back(screens[screenIndex]);
				currentScreens[0]->subscribe();
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