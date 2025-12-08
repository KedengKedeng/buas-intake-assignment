#include "screenSignals.hpp"

Signal<std::function<void()>> pushToCurrentScreenQueue{};
Signal<Screens, std::function<void()>> pushToScreenQueue{};

Signal<Screens> changeScreen{};
Signal<Screens> stackScreen{};
Signal<> closeScreen{};