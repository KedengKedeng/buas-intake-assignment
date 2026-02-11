#include "uiSignals.hpp"

Signal<int64_t, std::function<void(Tmpl8::Surface&, vec2<float>)>> drawOnTop{};
Signal<int64_t> removeDrawOnTop{};