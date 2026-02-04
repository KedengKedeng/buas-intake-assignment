#pragma once
#include "plot.hpp"
#include "object.hpp"
#include "interactable.hpp"
#include "collider.hpp"
#include "subscriptionManager.hpp"
#include "inventory.hpp"
#include <map>

class PlotObject : public Object, public Interactable, public Collider, public SubscriptionManager {
public:
	PlotObject(int64_t id, const vec2<float>& pos, const vec2<float>& size, std::shared_ptr<Plot> plot, std::shared_ptr<Inventory> inventory);
	~PlotObject();

	void addAnimal();

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;
	void process(float deltaTime) override;

	void subscribe() override;
private:
	std::vector<int64_t> animalIds = {};
	std::shared_ptr<Plot> plot_;
	std::shared_ptr<Inventory> inventory_;

	std::map<std::shared_ptr<Item>, int> availableForPickup = {};
};