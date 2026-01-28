#include "uiSignals.hpp"

Signal<std::shared_ptr<Tooltip>> showTooltip{};
Signal<int64_t> removeTooltip{};