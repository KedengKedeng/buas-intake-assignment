#include "recipeBook.hpp"

void RecipeBook::addRecipe(const std::vector<std::shared_ptr<Item>>& input, std::shared_ptr<Item> output) {
	std::string hashedRecipe = hashRecipe(input);
	recipes_[hashedRecipe] = output;
}

std::shared_ptr<Item> RecipeBook::lookup(const std::vector<std::shared_ptr<Item>>& items) {
	std::string hashed = hashRecipe(items);
	if (recipes_.count(hashed)) return recipes_[hashed];
	return nullptr;
}

std::string RecipeBook::hashRecipe(const std::vector<std::shared_ptr<Item>>& recipe) {
	std::string hashed(recipe[0]->name);

	for (auto& item = recipe.begin() + 1; item != recipe.end(); item++) 
		hashed += "|" + item->get()->name;
	
	return hashed;
}

RecipeBook recipeBook{};