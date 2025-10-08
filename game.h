#pragma once
#include "keyboardInput.hpp"
#include "screen.hpp"


namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { surface_ = surface; }
	void SetKeyboardInput(KeyboardInput input) { keyboardInput = input; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key) { keyboardInput.keyUp(key)->fire(); }
	void KeyDown(int key) { keyboardInput.keyDown(key)->fire(); }
private:
	Screen* screens[1];
	Screen* currentScreen;
	Surface* surface_;
	KeyboardInput keyboardInput;
};

}; // namespace Tmpl8