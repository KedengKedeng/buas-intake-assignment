#pragma once
#include "itemsRepository.hpp"
#include "recipeBook.hpp"

void setupRecipeList() {
	auto slimeItem = itemRepository().get(Items::BlueSlime);
	auto testItem = itemRepository().get(Items::Test);

	recipeBook.addRecipe({slimeItem, slimeItem}, testItem);
}