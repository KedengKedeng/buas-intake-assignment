#pragma once
#include "scene.hpp"
#include "scenes.hpp"
#include "surface.h"
#include "vec2.hpp"
#include <vector>
#include <queue>
#include <map>
#include <memory>

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface& surface ) { surface_ = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button) { if (button == 1) currentScenes[currentScenes.size() - 1]->onMouseUp(lastMousePos, lastMousePos); }
	void MouseDown(int button) { if (button == 1) currentScenes[currentScenes.size() - 1]->onMouseDown(lastMousePos, lastMousePos); }
	void MouseMove(int x, int y) {
		vec2<float> newPos(x, y);
		vec2 delta = newPos - lastMousePos;
		currentScenes[currentScenes.size() - 1]->onMouseMove(newPos, newPos, delta);
		lastMousePos = newPos;
	}
	void KeyUp(int key) { currentScenes[currentScenes.size() - 1]->keyUp(key); }
	void KeyDown(int key) { currentScenes[currentScenes.size() - 1]->keyDown(key); }
private:
	vec2<float> lastMousePos = vec2(0.0f);
	std::map<Scenes, std::shared_ptr<Scene>> scenes;
	std::vector<std::shared_ptr<Scene>> currentScenes;
	Surface surface_ = Surface(0, 0);
	std::queue<std::function<void()>> queue = {};
};

}; // namespace Tmpl8