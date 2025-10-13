#include "game.h"
#include "surface.h"
#include "button.hpp"
#include "playScreen.hpp"
#include "startScreen.hpp"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		keyboardInput = KeyboardInput();
		mouseInput = MouseInput();

		screens[0] = new PlayScreen(surface_);
		screens[1] = new StartScreen(surface_);
		currentScreen = screens[0];
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
		// clear the graphics window
		// print something in the graphics window
		//surface_->Print("hello world", 2, 2, 0xffffff);
		//// draw a sprite
		//rotatingGun.SetFrame(frame);
		//rotatingGun.Draw(surface_, 100, 100);
		//if (++frame == 36) frame = 0;
	}
};