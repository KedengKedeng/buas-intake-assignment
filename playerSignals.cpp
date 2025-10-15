#include "playerSignals.hpp"

Signal<Tmpl8::vec2&> walkSignal{};
Signal<Tmpl8::vec2&, Tmpl8::vec2&, Player&> requestMove{};