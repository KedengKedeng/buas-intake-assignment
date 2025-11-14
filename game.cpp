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
		currentScreen = screens[0];

		changeScreen.subscribe([this](int screenIndex) { 
			currentScreen->unsubscribe();
			currentScreen = screens[screenIndex]; 
			currentScreen->subscribe();
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
		currentScreen->process();
	}
};