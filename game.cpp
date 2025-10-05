#include "game.h"
#include "surface.h"
#include "button.hpp"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		keyboardInput = KeyboardInput();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(255 << 8);
		// print something in the graphics window
		screen->Print("hello world", 2, 2, 0xffffff);
		// draw a sprite
		rotatingGun.SetFrame(frame);
		rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;

		Button button = Button(std::string{ "test text" }, 10, 10, 200, 200, 4);
		button.draw(*screen);
	}
};