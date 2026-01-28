#pragma once
#include "signal.hpp"
#include "tooltip.hpp"
#include <memory>

extern Signal<std::shared_ptr<Tooltip>> showTooltip;
extern Signal<int64_t> removeTooltip;