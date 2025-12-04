#include "objectSignals.hpp"

Signal<int64_t> deleteObjectSignal{};

Signal<> cauldronInteracted{};

Signal<Tmpl8::vec2&, Tmpl8::vec2&, Object&> requestMove{};