#pragma once
#include "mouseInput.hpp"
#include "scene.hpp"
#include "scenes.hpp"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { surface_ = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button) { mouseInput.mouseUp(button)->execute(); }
	void MouseDown(int button) { mouseInput.mouseDown(button)->execute(); }
	void MouseMove(int x, int y) { mouseInput.setMousePos(vec2<float>(x, y))->execute(); }
	void KeyUp(int key) { currentScenes[currentScenes.size() - 1]->keyUp(key); }
	void KeyDown(int key) { currentScenes[currentScenes.size() - 1]->keyDown(key); }
private:
	std::map<Scenes, std::shared_ptr<Scene>> scenes;
	std::vector<std::shared_ptr<Scene>> currentScenes;
	Surface* surface_;
	MouseInput mouseInput;
	std::queue<std::function<void()>> queue = {};
};

}; // namespace Tmpl8