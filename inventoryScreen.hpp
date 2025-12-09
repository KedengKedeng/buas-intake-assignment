#pragma once
#include "screen.hpp"

class InventoryScreen : public Screen {
public:
	InventoryScreen(Tmpl8::Surface* surface);

	void draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) override;
private:

};