#include "objectSignals.hpp"

Signal<std::shared_ptr<Object>> createObjectSignal{};
Signal<int64_t> deleteObjectSignal{};

Signal<> cauldronInteracted{};
Signal<> cauldronInteractionEnded{};

Signal<> blowerInteracted{};
Signal<> blowerInteractionEnded{};
Signal<float> blowedSignal{};

Signal<vec2<float>, vec2<float>, Object&> requestMove{};