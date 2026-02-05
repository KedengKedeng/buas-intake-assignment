#pragma once 
#include "signal.hpp"
#include "vec2.hpp"

extern Signal<vec2<float>> onMouseDown;
extern Signal<> onMouseUp;
extern Signal<vec2<float>> mouseMoved;