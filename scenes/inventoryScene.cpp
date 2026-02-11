#include "inventoryScene.hpp"
#include "modal.hpp"
#include "sceneSignals.hpp"
#include "sceneCommands.hpp"
#include "inventorySlot.hpp"
#include "itemsRepository.hpp"
#include "itemSignals.hpp"
#include "boundingBox.hpp"

InventoryScene::InventoryScene(int width, int height, std::shared_ptr<Inventory> inventory) : 
	Scene(width, height), 
	inventory_(inventory) 
{
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<CloseSceneCommand>(); });

	vec2 size( 400.0f, 300.0f );
	insertObject(std::make_shared<Modal>(0, (vec2<float>(width, height) - size) / 2, size, []() {
		closeScene.emit();
	}, Justification::VERTICAL, vec2(10.0f), true));
}

void InventoryScene::draw(Tmpl8::Surface& surface, vec2<float> offset) const {
	auto modal = getObject<Modal>(0);
	auto items = inventory_->begin();
	for (auto containers = modal->begin(); containers != modal->end(); containers++) {
		auto container = std::dynamic_pointer_cast<ObjectContainer>(containers->second);
		for (auto inventorySlot = container->begin(); inventorySlot != container->end(); inventorySlot++) {
			auto slot = std::dynamic_pointer_cast<InventorySlot>(inventorySlot->second);

			if (items != inventory_->end()) {
				std::shared_ptr<Item> item_ = itemRepository().get(items->first);
				slot->setItem(item_, items->second);
				items++;
				continue;
			}

			slot->setItem(nullptr, 0);
		}
	}

	Scene::draw(surface, offset);
	drawDispatcher_.draw(surface, offset);
}

void InventoryScene::process(float deltaTime) {
	Scene::process(deltaTime);

	int itemCount = std::max(static_cast<int>(ceil(inventory_->getItemTypeCount() / maxItemsOnRow)), 3);
	if (itemCount != drawRows) {
		drawRows = itemCount;
		auto modal = getObject<Modal>(0);
		modal->clearObjects();

		int64_t id = 0;
		for (int x = 0; x < drawRows; x++) {
			modal->insertObject(std::make_shared<ObjectContainer>(id, vec2(0.0f), vec2(380.0f, inventorySlotSize.y), Justification::HORIZONTAL, vec2(10.0f, 0.0f)));
			auto horizontalContainer = modal->getInnerObject<ObjectContainer>(id);

			for (int y = 0; y < maxItemsOnRow; y++) {
				horizontalContainer->insertObject(std::make_shared<InventorySlot>(
					id, 
					vec2(0.0f), 
					inventorySlotSize,
					0,
					[this, modal](InventorySlot* slot, vec2<float>& pos) {
						BoundingBox containerBounds(modal->getPos(), modal->getSize());
						// drop item when user drags it out of the bounds of the modal
						if (!containerBounds.isInBounds(pos)) {
							auto item = slot->getItem();
							if (item == nullptr) return;
							pushToSceneQueue.emit(Scenes::Play, [item]() { itemDroppedFromInventory.emit(item); });
							inventory_->remove(item->id);
						}
					}
				));
				id++;
			}
			horizontalContainer->subscribe();
		}
	}
}