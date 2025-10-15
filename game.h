#pragma once
#include "keyboardInput.hpp"
#include "mouseInput.hpp"
#include "screen.hpp"
#include "template.h"

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
	void MouseUp(int button) { mouseInput.mouseUp(button)->execute(); }
	void MouseDown(int button) { mouseInput.mouseDown(button)->execute(); }
	void MouseMove(int x, int y) { mouseInput.setMousePos(x, y)->execute(); }
	void KeyUp(int key) { keyboardInput.keyUp(key)->execute(); }
	void KeyDown(int key) { keyboardInput.keyDown(key)->execute(); }
private:
	Screen* screens[2];
	Screen* currentScreen;
	Surface* surface_;
	KeyboardInput keyboardInput;
	MouseInput mouseInput;
};

}; // namespace Tmpl8