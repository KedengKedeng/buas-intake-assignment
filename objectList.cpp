#include "cauldron.hpp"
#include "objectRepository.hpp"
#include "objectList.hpp"

void setupObjectList() {
	objectRepository.insert("cauldron", std::make_shared<Cauldron>());
}