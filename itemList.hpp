#pragma once
#include "itemsRepository.hpp"
#include "recipeBook.hpp"

void setupRecipeList() {
	auto bottleItem = itemRepository().get(Items::BlueSlime);
	auto playerItem = itemRepository().get(Items::Test);

	recipeBook.addRecipe({bottleItem, bottleItem}, playerItem);
}