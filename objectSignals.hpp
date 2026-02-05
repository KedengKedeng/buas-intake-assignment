#pragma once
#include "signal.hpp"
#include "object.hpp"

extern Signal<std::shared_ptr<Object>> createObjectSignal;
extern Signal<int64_t> deleteObjectSignal;

extern Signal<> cauldronInteracted;
extern Signal<> cauldronInteractionEnded;

extern Signal<> blowerInteracted;
extern Signal<> blowerInteractionEnded;
extern Signal<float> blowedSignal;

extern Signal<vec2<float>, vec2<float>, Object&> requestMove;