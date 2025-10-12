#pragma once
#include <vector>
#include <functional>
#include "template.h"
#include "signal.hpp"

class Player;
extern Signal<Tmpl8::vec2> walkSignal;

#include "player.hpp"

extern Signal<Tmpl8::vec2, Tmpl8::vec2, Player> requestMove;