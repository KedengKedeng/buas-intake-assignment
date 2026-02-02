#pragma once
#include "signal.hpp"
#include "surface.h"
#include "vec2.hpp"

extern Signal<int64_t, std::function<void(Tmpl8::Surface*, const vec2<float>&)>> drawOnTop;
extern Signal<int64_t> removeDrawOnTop;