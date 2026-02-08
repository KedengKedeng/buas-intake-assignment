#pragma once
#include "itemsRepository.hpp"
#include "recipeBook.hpp"

void setupRecipeList() {
	auto blueSlime = itemRepository().get(Items::BlueSlime);
	auto greenSlime = itemRepository().get(Items::GreenSlime);
	auto iceGem = itemRepository().get(Items::IceGem);
	auto windGem = itemRepository().get(Items::WindGem);
	auto earthGem = itemRepository().get(Items::EarthGem);
	auto fireGem = itemRepository().get(Items::FireGem);

	auto slipperyOrb = itemRepository().get(Items::SlipperyOrb);
	recipeBook.addRecipe({ blueSlime, blueSlime }, slipperyOrb);

	auto stickyOrb = itemRepository().get(Items::SlimeTape);
	recipeBook.addRecipe({ greenSlime, greenSlime }, stickyOrb);

	auto iceScates = itemRepository().get(Items::IceScates);
	recipeBook.addRecipe({ iceGem, iceGem }, iceScates);

	auto windCharge = itemRepository().get(Items::WindCharge);
	recipeBook.addRecipe({ windGem, windGem }, windCharge);

	auto clayBall = itemRepository().get(Items::ClayBall);
	recipeBook.addRecipe({ earthGem, earthGem }, clayBall);

	auto fireCharge = itemRepository().get(Items::FireCharge);
	recipeBook.addRecipe({ fireGem, fireGem }, fireCharge);

	auto slimeTape = itemRepository().get(Items::SlimeTape);
	recipeBook.addRecipe({ blueSlime, greenSlime }, slimeTape);
	recipeBook.addRecipe({ greenSlime, blueSlime }, slimeTape);

	auto rainBoots = itemRepository().get(Items::RainBoots);
	recipeBook.addRecipe({ blueSlime, iceGem }, rainBoots);
	recipeBook.addRecipe({ iceGem, blueSlime }, rainBoots);

	auto gliderWings = itemRepository().get(Items::GliderWings);
	recipeBook.addRecipe({ blueSlime, windGem }, gliderWings);
	recipeBook.addRecipe({ windGem, blueSlime }, gliderWings);

	auto stoneWheel = itemRepository().get(Items::StoneWheel);
	recipeBook.addRecipe({ blueSlime, earthGem }, stoneWheel);
	recipeBook.addRecipe({ earthGem, blueSlime }, stoneWheel);

	auto rocketBooster = itemRepository().get(Items::RocketBooster);
	recipeBook.addRecipe({ blueSlime, fireGem }, rocketBooster);
	recipeBook.addRecipe({ fireGem, blueSlime }, rocketBooster);

	auto burnCream = itemRepository().get(Items::BurnCream);
	recipeBook.addRecipe({ greenSlime, iceGem }, burnCream);
	recipeBook.addRecipe({ iceGem, greenSlime }, burnCream);

	auto grapplingHook = itemRepository().get(Items::GrapplingHook);
	recipeBook.addRecipe({ greenSlime, windGem }, grapplingHook);
	recipeBook.addRecipe({ windGem, greenSlime }, grapplingHook);

	auto climbingGloves = itemRepository().get(Items::ClimbingGloves);
	recipeBook.addRecipe({ greenSlime, earthGem }, climbingGloves);
	recipeBook.addRecipe({ earthGem, greenSlime }, climbingGloves);

	auto stickyBomb = itemRepository().get(Items::StickyBomb);
	recipeBook.addRecipe({ greenSlime, fireGem }, stickyBomb);
	recipeBook.addRecipe({ fireGem, greenSlime }, stickyBomb);

	auto stormInABottle = itemRepository().get(Items::StormInABottle);
	recipeBook.addRecipe({ windGem, iceGem }, stormInABottle);
	recipeBook.addRecipe({ iceGem, windGem }, stormInABottle);

	auto shipInABottle = itemRepository().get(Items::ShipInABottle);
	recipeBook.addRecipe({ windGem, earthGem }, shipInABottle);
	recipeBook.addRecipe({ earthGem, windGem }, shipInABottle);

	auto lightningGem = itemRepository().get(Items::LightningGem);
	recipeBook.addRecipe({ windGem, fireGem }, lightningGem);
	recipeBook.addRecipe({ fireGem, windGem }, lightningGem);

	auto muddyBlob = itemRepository().get(Items::MuddyBlob);
	recipeBook.addRecipe({ iceGem, earthGem }, muddyBlob);
	recipeBook.addRecipe({ earthGem, iceGem }, muddyBlob);

	auto obsidianGem = itemRepository().get(Items::ObsidianGem);
	recipeBook.addRecipe({ iceGem, fireGem }, obsidianGem);
	recipeBook.addRecipe({ fireGem, iceGem }, obsidianGem);

	auto magmaBall = itemRepository().get(Items::MagmaBall);
	recipeBook.addRecipe({ earthGem, fireGem }, magmaBall);
	recipeBook.addRecipe({ fireGem, earthGem }, magmaBall);
}