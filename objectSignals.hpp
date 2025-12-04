#pragma once
#include "signal.hpp"
#include "template.h"
#include "object.hpp"

extern Signal<int64_t> deleteObjectSignal;

extern Signal<> cauldronInteracted;

extern Signal<Tmpl8::vec2&, Tmpl8::vec2&, Object&> requestMove;