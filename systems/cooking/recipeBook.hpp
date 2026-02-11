#pragma once
#include <unordered_map>
#include <string>
#include "item.hpp"
#include <memory>
#include <optional>

class RecipeBook {
public:
	void addRecipe(const std::vector<std::shared_ptr<Item>>& input, std::shared_ptr<Item> output);
	std::optional<std::shared_ptr<Item>> lookup(const std::vector<std::shared_ptr<Item>>& items) const;
private:
	std::string hashRecipe(const std::vector<std::shared_ptr<Item>>& recipe) const;
	std::unordered_map<std::string, std::shared_ptr<Item>> recipes_ = {};
};

extern RecipeBook recipeBook;