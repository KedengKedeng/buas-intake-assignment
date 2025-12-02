#pragma once
#include <map>
#include <string>
#include <memory>
#include "object.hpp"

class ObjectRepository {
public:
	void insert(std::string& name, std::shared_ptr<Object> object) { registry_.insert({ name, object }); }
	std::shared_ptr<Object> get(std::string& name) { return registry_[name]; }
private:
	std::map<std::string, std::shared_ptr<Object>> registry_ = {};
};

extern ObjectRepository objectRepository;