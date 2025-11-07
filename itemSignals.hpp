#pragma once
#include "signal.hpp"
#include "item.hpp"

extern Signal<std::shared_ptr<Item>> itemPickedUp;
extern Signal<std::shared_ptr<Item>> itemDropped;