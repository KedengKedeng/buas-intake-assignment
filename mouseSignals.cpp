#include "mouseSignals.hpp"

Signal<Tmpl8::vec2&> onMouseDown{};
Signal<> onMouseUp{};
Signal<Tmpl8::vec2&> mouseMoved{};