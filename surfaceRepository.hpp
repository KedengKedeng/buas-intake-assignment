#pragma once
#include <map>
#include <string>
#include <memory>
#include "surface.h"

class SurfaceRepository {
public:
	void insert(const std::string& name, std::shared_ptr<Tmpl8::Surface> surface) { registry_.insert({ name, surface }); }
	std::shared_ptr<Tmpl8::Surface> get(const std::string& name) { return registry_.at(name); }
private:
	std::map<std::string, std::shared_ptr<Tmpl8::Surface>> registry_ = {};
};

extern SurfaceRepository surfaceRepository;
