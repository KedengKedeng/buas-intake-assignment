#include "inventoryScreen.hpp"
#include "modal.hpp"
#include "screenSignals.hpp"
#include "screenCommands.hpp"
#include "inventorySlot.hpp"
#include "itemsRepository.hpp"
#include "itemSignals.hpp"
#include "boundingBox.hpp"

InventoryScreen::InventoryScreen(Tmpl8::Surface* surface, std::shared_ptr<Inventory> inventory) 
	: Screen(surface), inventory_(inventory) {
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<CloseScreenCommand>(); });

	vec2 size( 400.0f, 300.0f );
	insertObject(std::make_shared<Modal>(0, vec2<float>(surface->GetWidth(), surface->GetHeight()) / 2 - size / 2, size, []() {
		closeScreen.emit();
	}, Justification::VERTICAL, vec2(10.0f), true));
}

void InventoryScreen::draw(Tmpl8::Surface* surface, const vec2<float>& offset) {
	auto modal = getObject<Modal>(0);
	auto items = inventory_->begin();
	for (auto containers = modal->begin(); containers != modal->end(); containers++) {
		auto container = std::dynamic_pointer_cast<Container>(containers->second);
		for (auto inventorySlot = container->begin(); inventorySlot != container->end(); inventorySlot++) {
			auto slot = std::dynamic_pointer_cast<InventorySlot>(inventorySlot->second);

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
	drawDispatcher_.draw(surface, offset);
}

void InventoryScreen::process(float deltaTime) {
	int itemCount = std::max(static_cast<int>(ceil(inventory_->getItemTypeCount() / maxItemsOnRow)), 3);
	if (itemCount != drawRows) {
		drawRows = itemCount;
		auto container = getObject<Modal>(0);
		container->clearObjects();

		int64_t id = 0;
		for (int x = 0; x < drawRows; x++) {
			container->insertObject(std::make_shared<Container>(id, vec2(0.0f), vec2(380.0f, inventorySlotSize.y), Justification::HORIZONTAL, vec2(10.0f, 0.0f)));
			auto horizontalContainer = container->getInnerObject<Container>(id);

			for (int y = 0; y < maxItemsOnRow; y++) {
				horizontalContainer->insertObject(std::make_shared<InventorySlot>(
					id, 
					vec2(0.0f), 
					inventorySlotSize, 
					nullptr, 
					0,
					[this, container](InventorySlot* slot, vec2<float>& pos) {
						BoundingBox containerBounds(container->getPos(), container->getSize());
						// drop item when user drags it out of the bounds of the modal
						if (!containerBounds.isInBounds(pos)) {
							auto item = slot->getItem();
							if (item == nullptr) return;
							pushToScreenQueue.emit(Screens::Play, [item]() { itemDroppedFromInventory.emit(item); });
							inventory_->remove(item->name);
						}
					}
				));
				id++;
			}
			horizontalContainer->subscribe();
		}
	}
}