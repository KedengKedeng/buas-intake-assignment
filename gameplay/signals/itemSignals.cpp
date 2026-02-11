#include "itemSignals.hpp"

Signal<std::shared_ptr<Item>> itemPickedUp{};
Signal<std::shared_ptr<Item>> itemDropped{};
Signal<std::shared_ptr<Item>> itemDroppedFromInventory{};