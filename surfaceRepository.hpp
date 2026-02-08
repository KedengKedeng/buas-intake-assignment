#pragma once
#include <map>
#include <memory>
#include "surface.h"

enum class Surfaces {
	PlayerIdleLeft,
	PlayerIdleRight,
	PlayerWalkLeft,
	PlayerWalkRight,

	PenguinIdleLeft,
	PenguinIdleRight,
	PenguinWalkLeft,
	PenguinWalkRight,

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

	BlueSlime,
	GreenSlime,
	IceGem,
	WindGem,
	EarthGem,
	FireGem,

	SlipperyOrb,
	SlimeTape,
	RainBoots,
	GliderWings,
	StoneWheel,
	RocketBooster,
	StickyOrb,
	BurnCream,
	GrapplingHook,
	ClimbingGloves,
	StickyBomb,
	StormInABottle,
	WindCharge,
	ShipInABottle,
	LightningGem,
	IceScates,
	MuddyBlob,
	ObsidianGem,
	ClayBall,
	MagmaBall,
	FireCharge,

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
