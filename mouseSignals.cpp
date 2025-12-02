#include "mouseSignals.hpp"

Signal<Tmpl8::vec2&> mousePressed{};
Signal<> mouseReleased{};
Signal<Tmpl8::vec2&> mouseMoved{};