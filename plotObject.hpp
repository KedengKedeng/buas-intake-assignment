#pragma once
#include "plot.hpp"
#include "object.hpp"
#include "interactable.hpp"
#include "tooltip.hpp"

class PlotObject : public Object, public Interactable {
public:
	PlotObject(int64_t id, const vec2<float>& pos, const vec2<float>& size, std::shared_ptr<Plot> plot);
	~PlotObject();

	void addAnimal();

	void draw(Tmpl8::Surface* surface, const vec2<float>& offset) override;

	void subscribe() override;
private:
	std::vector<int64_t> animalIds = {};
	std::shared_ptr<Plot> plot_;

	Tooltip tooltip_;
};