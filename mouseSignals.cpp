#include "mouseSignals.hpp"

Signal<vec2<float>&> onMouseDown{};
Signal<> onMouseUp{};
Signal<vec2<float>&> mouseMoved{};