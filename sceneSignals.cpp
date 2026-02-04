#include "sceneSignals.hpp"

Signal<std::function<void()>> pushToCurrentSceneQueue{};
Signal<Scenes, std::function<void()>> pushToSceneQueue{};

Signal<Scenes> changeScene{};
Signal<Scenes> stackScene{};
Signal<> closeScene{};