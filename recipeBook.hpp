#pragma once
#include <unordered_map>
#include <string>
#include "item.hpp"

class RecipeBook {
public:
	void addRecipe(const std::vector<std::shared_ptr<Item>>& input, std::shared_ptr<Item> output);
	std::shared_ptr<Item> lookup(const std::vector<std::shared_ptr<Item>>& items);
private:
	std::string hashRecipe(const std::vector<std::shared_ptr<Item>>& recipe);
	std::unordered_map<std::string, std::shared_ptr<Item>> recipes_ = {};
};

extern RecipeBook recipeBook;