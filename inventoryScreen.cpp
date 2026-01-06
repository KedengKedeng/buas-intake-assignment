#include "inventoryScreen.hpp"
#include "modal.hpp"
#include "screenSignals.hpp"
#include "screenCommands.hpp"
#include "inventorySlot.hpp"
#include "itemsRepository.hpp"
#include "itemSignals.hpp"

InventoryScreen::InventoryScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory) 
	: Screen(surface), inventory_(inventory) {
	keyboardInput_.registerHandler("escape", []() {return std::make_unique<CloseScreenCommand>(); });

	Tmpl8::vec2 size = { 400, 300 };
	insertObject(std::make_unique<Modal>(0, Tmpl8::vec2(surface->GetWidth(), surface->GetHeight()) / 2 - size / 2, size, []() {
		closeScreen.emit();
	}, Justification::VERTICAL));
}

void InventoryScreen::draw(Tmpl8::Surface* surface, const Tmpl8::vec2& offset) {
	auto modal = getObject<Modal>(0);
	auto items = inventory_->begin();
	for (auto containers = modal->begin(); containers != modal->end(); containers++) {
		Container* container = dynamic_cast<Container*>(containers->second.get());
		for (auto inventorySlot = container->begin(); inventorySlot != container->end(); inventorySlot++) {
			InventorySlot* slot = dynamic_cast<InventorySlot*>(inventorySlot->second.get());

			if (items != inventory_->end()) {
				std::string itemName = const_cast<std::string&>(items->first);
				std::shared_ptr<Item> item_ = itemRepository.get(itemName);
				slot->setItem(item_, items->second);
				items++;
				continue;
			}

			slot->setItem(nullptr, 0);
		}
	}

	Screen::draw(surface, offset);
}

void InventoryScreen::process(float deltaTime) {
	int itemCount = std::max(static_cast<int>(ceil(inventory_->getItemTypeCount() / maxItemsOnRow)), 3);
	if (itemCount != drawRows) {
		drawRows = itemCount;
		auto container = getObject<Modal>(0);
		container->clearObjects();

		int64_t id = 0;
		for (int x = 0; x < drawRows; x++) {
			container->insertObject(std::make_unique<Container>(id, Tmpl8::vec2(0), Tmpl8::vec2(380.0f, inventorySlotSize.y), Justification::HORIZONTAL));
			auto horizontalContainer = container->getInnerObject<Container>(id);

			for (int y = 0; y < maxItemsOnRow; y++) {
				horizontalContainer->insertObject(std::make_unique<InventorySlot>(
					id, 
					Tmpl8::vec2(0), 
					inventorySlotSize, 
					nullptr, 
					0,
					[this, container](InventorySlot* slot, Tmpl8::vec2& pos) {
						BoundingBox containerBounds = BoundingBox(container->getPos(), container->getSize());
						// drop item when user drags it out of the bounds of the modal
						if (!containerBounds.isInBounds(BoundingBox(pos, Tmpl8::vec2(0)))) {
							auto item = slot->getItem();
							if (item == nullptr) return;
							inventory_->remove(item->name);
							pushToScreenQueue.emit(Screens::Play, [item]() { itemDroppedFromInventory.emit(item); });
						}
					}
				));
				id++;
			}
			horizontalContainer->subscribe();
		}
	}
}