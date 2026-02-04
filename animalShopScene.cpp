#include "animalShopScene.hpp"
#include "modal.hpp"
#include "sceneCommands.hpp"
#include "sceneSignals.hpp"
#include "creatureTypeRepository.hpp"
#include "animalShopItem.hpp"

AnimalShopScene::AnimalShopScene(Tmpl8::Surface* surface, std::shared_ptr<Wallet> wallet, std::shared_ptr<Husbandry> husbandry) :
	Scene(surface),
	wallet_(wallet),
	husbandry_(husbandry)
{
	keyboardInput_.registerHandler(KeyFunctions::Escape, []() {return std::make_unique<CloseSceneCommand>(); });

	vec2 modalSize = vec2(400.0f, 400.0f);
	vec2 modalPos = (vec2<float>(surface->GetWidth(), surface->GetHeight()) - modalSize) / 2;
	std::shared_ptr<Modal> modal = std::make_shared<Modal>(
		0, 
		modalPos, 
		modalSize, 
		[this]() {closeScene.emit(); }, 
		Justification::VERTICAL,
		vec2(10.0f),
		true
	);

	int id = 0;
	for (auto& it = creatureTypeRepository.begin(); it != creatureTypeRepository.end(); it++) {
		modal->insertObject(std::make_shared<AnimalShopItem>(
			id, 
			vec2(0.0f), 
			vec2(modalSize.x - modal->getPadding().x * 2, 100.0f), 
			it->second, 
			wallet_, 
			husbandry_
		));
		id++;
	}

	insertObject(modal);
}