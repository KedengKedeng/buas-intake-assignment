#pragma once
#include <map>
#include <memory>
#include "surface.h"
#include "surfaces.hpp"

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
