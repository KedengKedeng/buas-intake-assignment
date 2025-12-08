#pragma once 
#include "signal.hpp"
#include "screens.hpp"

extern Signal<std::function<void()>> pushToCurrentScreenQueue;
extern Signal<Screens, std::function<void()>> pushToScreenQueue;

extern Signal<Screens> changeScreen;
extern Signal<Screens> stackScreen;
extern Signal<> closeScreen;