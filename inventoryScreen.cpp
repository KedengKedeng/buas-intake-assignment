#include "inventoryScreen.hpp"
#include "modal.hpp"
#include "screenSignals.hpp"
#include "screenCommands.hpp"

InventoryScreen::InventoryScreen(Tmpl8::Surface* surface) : Screen(surface) {
	keyboardInput_.registerHandler(std::string("escape"), []() {return std::make_unique<CloseScreenCommand>(); });

	Tmpl8::vec2 size = { 200, 200 };
	insertObject(std::make_unique<Modal>(0, Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) / 2 - size / 2, size, []() {
		closeScreen.emit();
	}, Justification::VERTICAL));
}

void InventoryScreen::draw(Tmpl8::Surface* surface, Tmpl8::vec2& offset) {
	Screen::draw(surface, offset);
}