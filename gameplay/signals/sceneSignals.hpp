#pragma once 
#include "signal.hpp"
#include "scenes.hpp"

extern Signal<std::function<void()>> pushToCurrentSceneQueue;
extern Signal<Scenes, std::function<void()>> pushToSceneQueue;

extern Signal<Scenes> changeScene;
extern Signal<Scenes> stackScene;
extern Signal<> closeScene;