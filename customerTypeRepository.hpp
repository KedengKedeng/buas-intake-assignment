#pragma once
#include <map>
#include <memory>
#include "customerType.hpp"

class CustomerTypeRepository {
public:
	CustomerTypeRepository();

	void insert(std::shared_ptr<CustomerType> type) { registry_.insert({ type->id, type }); }
	std::shared_ptr<CustomerType> get(CustomerTypes type) { return registry_.at(type); }
private:
	std::map<CustomerTypes, std::shared_ptr<CustomerType>> registry_ = {};
};

static CustomerTypeRepository& customerTypeRepository() {
	static CustomerTypeRepository repo;
	return repo;
}
