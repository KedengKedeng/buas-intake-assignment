#pragma once
#include <map>
#include <memory>
#include "surface.h"

enum class Surfaces {
	WaterBottle,

	PlayerIdleLeft,
	PlayerIdleRight,
	PlayerWalkLeft,
	PlayerWalkRight,

	BlueSlimeIdleLeft,
	BlueSlimeIdleRight,
	BlueSlimeWalkLeft,
	BlueSlimeWalkRight,
	GreenSlimeIdleLeft,
	GreenSlimeIdleRight,
	GreenSlimeWalkLeft,
	GreenSlimeWalkRight,
	IceDragonIdleLeft,
	IceDragonIdleRight,
	IceDragonWalkLeft,
	IceDragonWalkRight,
	WindDragonIdleLeft,
	WindDragonIdleRight,
	WindDragonWalkLeft,
	WindDragonWalkRight,
	EarthDragonIdleLeft,
	EarthDragonIdleRight,
	EarthDragonWalkLeft,
	EarthDragonWalkRight,
	FireDragonIdleLeft,
	FireDragonIdleRight,
	FireDragonWalkLeft,
	FireDragonWalkRight,

	EmptyCauldron,
	EmptyBurningCauldron,
	FilledCauldron,
	FilledBurningCauldron,
	CauldronCloseupFront,
	CauldronCloseupBack,
	CauldronCloseupFire,
	CauldronCloseupFilled,

	Spoon,
	Blower,

	Floor
};

class SurfaceRepository {
public:
	SurfaceRepository();

	void insert(Surfaces identifier, std::shared_ptr<Tmpl8::Surface> surface) { registry_.insert({ identifier, surface }); }
	std::shared_ptr<Tmpl8::Surface> get(Surfaces surface) { return registry_.at(surface); }
private:
	std::map<Surfaces, std::shared_ptr<Tmpl8::Surface>> registry_ = {};
};

static SurfaceRepository& surfaceRepository() {
	static SurfaceRepository repo;
	return repo;
}
