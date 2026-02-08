#pragma once
#include "plot.hpp"
#include "object.hpp"
#include "interactable.hpp"
#include "collider.hpp"
#include "subscriptionManager.hpp"
#include "inventory.hpp"
#include "husbandry.hpp"
#include "spriteRepository.hpp"

class PlotObject : public Object, public Interactable, public Collider, public SubscriptionManager {
public:
	PlotObject(
		int64_t id, 
		vec2<float> pos, 
		vec2<float> size, 
		std::shared_ptr<Plot> plot, 
		std::shared_ptr<Inventory> inventory, 
		std::shared_ptr<Husbandry> husbandry
	);
	~PlotObject();

	void addAnimal();

	void draw(Tmpl8::Surface* surface, vec2<float> offset) const override;
	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::vector<int64_t> animalIds = {};
	std::shared_ptr<Plot> plot_;
	std::shared_ptr<Inventory> inventory_;
	std::shared_ptr<Husbandry> husbandry_;

	AnimatedSprite producedItemSprite;
	int availableForPickup = 0;
};